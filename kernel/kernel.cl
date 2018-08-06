/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:28:29 by jhache            #+#    #+#             */
/*   Updated: 2018/08/06 18:57:26 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_common_structs.h"

/*
** t_rt_result: Stands for: RayTraceResult. Stores the infos about a ray.
**
** -obj: the touched object.
** -pos: where the intersection is located.
** -normal: normal vector of the surface at the intersection point.
** -dist: distance of the intersection from the ray's origin.
** -shadow_amount: used for the light traveling threw refractive objects.
*/
typedef struct				s_rt_result
{
	constant t_object		*obj;
	float3					pos;
	float3					normal;
	float					dist;
	float3					shadow_amount;
}							t_rt_result;

#include "rotate.cl"
#include "color.cl"
#include "objects/cone.cl"
#include "objects/cylinder.cl"
#include "objects/plane.cl"
#include "objects/sphere.cl"
#include "objects/disk.cl"
#include "objects/triangle.cl"
#include "objects/paraboloid.cl"
#include "objects/meshes.cl"
#include "shadow_ray.cl"
#include "render.cl"
#include "stack_functions.cl"
#include "teleport_ray.cl"
#include "secondary_rays.cl"

kernel void	render_frame(
		write_only image2d_t output,
		constant t_cam *cam,
		constant t_object *objs,
		constant t_light *lights,
		private unsigned int objs_num,
		private unsigned int lights_num,
		private unsigned int w,
		private unsigned int h,
		local t_ray *stack,
		private t_clint depth,
		private char no_negative,/*,
		private float3 bg_color,*/
//		private unsigned int endian,	//gerer par sdl je crois, a supprimer
		constant t_mesh_triangle *triangles,
		private unsigned int seed
		)
{
	unsigned int	x;
	unsigned int	y;
	t_rt_result		r;
	t_cluint		stack_size;
	t_cluint		offset;
	t_ray			curr_ray;
	float3			color;
//
	float3			bg_color;
	set_to_zero(&bg_color);
//
	x = get_global_id(0);
	y = get_global_id(1);
	stack_size = 0;
	offset = (get_local_id(0) + get_local_id(1) * get_local_size(0))
		* (depth + 1);
	curr_ray.pos = cam->pos;
	curr_ray.dir = compute_pixel_coor(cam, w, h, x, y, seed);
	curr_ray.clr_contrib = 1.f;
	curr_ray.depth = depth;
	stack_push(stack, curr_ray, &stack_size, offset);
	set_to_zero(&color);
	while (stack_size != 0)
	{
		curr_ray = stack_pop(stack, &stack_size, offset);
		if (!raytrace(objs, triangles, objs_num, curr_ray.pos, curr_ray.dir, &r, no_negative))
			color += bg_color * curr_ray.clr_contrib;
		else
		{
			if (r.obj->mat.props != MAT_PORTAL)
				color += shading(objs, objs_num, lights, lights_num, &r, triangles, no_negative)
					* curr_ray.clr_contrib;
			else
				teleport_ray(curr_ray, &r, stack, &stack_size, offset);
			if (r.obj->mat.props == MAT_REFLECTIVE
					|| r.obj->mat.props == MAT_REFRACTIVE)
				compute_secondary_rays(curr_ray, &r, stack, &stack_size, offset);
		}
	}
	write_imageui(output, (int2)(x, y), (uint4)(color.z * 255, color.y * 255, color.x * 255, 255));
}
