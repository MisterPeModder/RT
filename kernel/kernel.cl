/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:28:29 by jhache            #+#    #+#             */
/*   Updated: 2018/06/24 18:54:04 by yguaye           ###   ########.fr       */
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
*/
typedef struct				s_rt_result
{
	constant t_object		*obj;
	t_clfloat3				pos;
	t_clfloat3				normal;
	float					dist;
}							t_rt_result;

#include "rotate.cl"
#include "color.cl"
#include "objects/cone.cl"
#include "objects/cylinder.cl"
#include "objects/plane.cl"
#include "objects/sphere.cl"
#include "objects/disk.cl"
#include "objects/triangle.cl"
#include "objects/cube.cl"
#include "objects/pyramid.cl"
#include "objects/paraboloid.cl"
#include "render.cl"

kernel void	render_frame(
		write_only image2d_t output,
		constant t_cam *cam,
		constant t_object *objs,
		constant t_light *lights,
		private size_t objs_num,
		private size_t lights_num,
		private unsigned int w,
		private unsigned int h,
		private char no_negative
		)
{
	unsigned int	x;
	unsigned int	y;
	float3			color;
	float3			unit;
	t_rt_result		r;
//
	float3			bg_color;
	bg_color.x = 0;
	bg_color.y = 0;
	bg_color.z = 0;
//
	x = get_global_id(0);
	y = get_global_id(1);
	unit = compute_pixel_coor(cam, w, h, x, y);
	if (!raytrace(objs, objs_num, cam->pos, unit, &r, no_negative))
		color = bg_color;
	else
		color = shading(objs, objs_num, lights, lights_num, &r, no_negative);
	write_imageui(output, (int2)(x, y), (uint4)(color.z * 255, color.y * 255, color.x * 255, 255));
}
