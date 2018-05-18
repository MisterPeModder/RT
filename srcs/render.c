/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:32:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/18 14:13:08 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <float.h>
#include <math.h>
#include "rtv1.h"

static t_vec3f		compute_pixel_coor(t_scene *scene, t_img *img,
		unsigned int pix_x, unsigned int pix_y)
{
	t_vec3f			vec;
	float			fov;

	fov = tan(scene->cam.fov / 2);
	vec.x = (2 * ((pix_x + 0.5) / img->w) - 1) * img->w / (float)img->h * fov;
	vec.y = (1 - 2 * ((pix_y + 0.5) / img->h)) * fov;
	vec.z = -1;
	rotate_x(&vec, scene->cam.angle.x);
	rotate_y(&vec, scene->cam.angle.y);
	rotate_z(&vec, scene->cam.angle.z);
	vec3f_normalize(&vec, &vec);
	return (vec);
}

/*
** raytrace: Handles the ray tracing operation.
**
** -scene: the scene instance.
** -o: origin of the ray.
** -u: unit vector (direction) of that ray.
** -r: where the result will be stored.
**
** returns: 1 if an intersection has been found, 0 otherwise.
*/

static int			raytrace(t_scene *scene, t_vec3f *o, t_vec3f *u,
		t_rt_result *r)
{
	size_t			i;
	float			d;
	float			tmp;

	i = 0;
	d = FLT_MAX;
	while (i < scene->objs_num)
	{
		tmp = scene->objs[i].type->intersect(&scene->objs[i], o, u);
		if (tmp > 0 && tmp < d)
		{
			r->obj = scene->objs + i;
			d = tmp;
		}
		++i;
	}
	if (d == FLT_MAX)
		return (0);
	r->dist = d;
	vec3f_mul(u, d, &r->pos);
	vec3f_add(o, &r->pos, &r->pos);
	r->obj->type->normal(r->obj, r);
	return (1);
}

/*
** shading: Handles the shading using the Phong algorithm.
**
** -scene: the scene instance.
** -r: the primary ray's raytrace result.
** -c: where the color of the pixel will be stored.
*/

static void			shading(t_scene *scene, t_rt_result *r, t_vec3f *c)
{
	size_t			i;
	t_vec3f			lvec;
	t_rt_result		sink;
	t_vec3f			start;

	i = 0;
	vec3f_div(&r->obj->color, 10, c);
	while (i < scene->lights_num)
	{
		vec3f_normalize(vec3f_sub(&scene->lights[i].pos, &r->pos, &lvec),
				&lvec);
		vec3f_add(&r->pos, vec3f_mul(&lvec, 0.001, &start), &start);
		if (!raytrace(scene, &start, &lvec, &sink)
				|| vec3f_norm(vec3f_sub(&scene->lights[i].pos, &r->pos, &start))
				< sink.dist)
			colorize(scene->lights[i], lvec, r, c);
		++i;
	}
}

/*
** render_frame: Handles everything. Literally.
**
** -scene: the scene instance.
** -img: the frame buffer instance.
*/

void				render_frame(t_scene *scene, t_img *img)
{
	unsigned int	i;
	unsigned int	j;
	t_vec3f			unit;
	t_rt_result		r;
	t_vec3f			c;

	i = 0;
	while (i < img->h)
	{
		j = 0;
		while (j < img->w)
		{
			unit = compute_pixel_coor(scene, img, j, i);
			if (!raytrace(scene, &scene->cam.pos, &unit, &r))
				vec3f_cpy(&scene->bg_color, &c);
			else
				shading(scene, &r, &c);
			color_fill(img->data[j++][i], c.x * 255, c.y * 255, c.z * 255);
		}
		++i;
	}
}
