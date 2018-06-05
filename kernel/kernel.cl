/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kernel.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 17:28:29 by jhache            #+#    #+#             */
/*   Updated: 2018/06/06 00:13:51 by yguaye           ###   ########.fr       */
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
#include "render.cl"

kernel void	render_frame(
		write_only image2d_t output,
		constant t_cam *cam,
		constant t_object *objs,
		constant t_light *lights,
		private size_t objs_num,
		private size_t lights_num,
		private unsigned int w,
		private unsigned int h
		//private float3 bg_color,
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
//	printf("x: %u, y: %u\n", x, y);
	unit = compute_pixel_coor(cam, w, h, x, y);
	if (!raytrace(objs, objs_num, cam->pos, unit, &r))
		color = bg_color;
	else
		color = shading(objs, objs_num, lights, lights_num, &r);
	write_imageui(output, (int2)(x, y), (uint4)(color.z * 255, color.y * 255, color.x * 255, 255));
}


/*__kernel void a_frame(
  private unsigned int x_size,
  private unsigned int y_size,
  write_only image2d_t output)
  {
  private int2 coord;

  coord.x = get_global_id(0);
  coord.y = get_global_id(1);
  write_imageui(output, coord, (uint4)(255 * (coord.x / (float)x_size), 0,
  255 * (coord.y / (float)y_size), 0));
  }
*/
