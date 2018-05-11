/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:32:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/11 14:26:00 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <float.h>
#include <math.h>
#include "rtv1.h"

#include <stdio.h>

//CONVERTED
static t_vec3f		compute_pixel_coor(t_scene *scene, t_img *img, unsigned int pix_x, unsigned int pix_y)
{
	t_vec3f			vec;
	float			fov;

	fov = tan(scene->cam.fov / 2);
	vec.x = (2 * ((pix_x + 0.5) / img->w) - 1) * (img->w / img->h) * fov;
	vec.y = (1 - 2 * ((pix_y + 0.5) / img->h)) * fov;
	vec.z = -1;
	vec3f_normalize(&vec, &vec);
	return (vec);
}

//CONVERTED
static int			get_hitpos(t_scene *scene, t_vec3f *o, t_vec3f *u, t_rt_result *r)
{
	size_t			i;
	float			d;
	float			tmp;

	i = 0;
	d = FLT_MAX;
	while (i < scene->objs_num)
	{
		tmp = scene->objs[i].intersect(&scene->objs[i], o, u);
		if (tmp < d)
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
	r->obj->normal(r->obj, &r->pos, &r->normal);
	return (1);
}

//CONVERTED
static void			shading(t_scene *scene, t_rt_result *r, t_color c)
{
	size_t			i;
	t_vec3f			lvec;
	t_rt_result		sink;
	t_vec3f			start;
	float			power;

	i = 0;
	color_fill(c, 0, 0, 0);
	while (i < scene->lights_num)
	{
		vec3f_normalize(vec3f_sub(&r->pos, &scene->lights[i], &lvec), &lvec);
		vec3f_add(&r->pos, vec3f_mul(&lvec, 0.01, &start), &start);
		if (get_hitpos(scene, &start, &lvec, &sink))
		{
			power = r->obj->brightness * vec3f_dot_product(&lvec, &r->normal);
/*			dprintf(2, "power: %.4f\n", power);*/
			color_brightness(c, r->obj->color, power);
		}
		++i;
	}
}

//CONVERTED
void				render_frame(t_scene *scene, t_img *img)
{
	unsigned int	i;
	unsigned int	j;
	t_vec3f			unit;
	t_rt_result		r;

	i = 0;
	while (i < img->h)
	{
		j = 0;
		while (j < img->w)
		{
			unit = compute_pixel_coor(scene, img, j, i);
			if (!get_hitpos(scene, &scene->cam.pos, &unit, &r))
				color_fill(img->data[j][i], scene->bg_color[0], scene->bg_color[1], scene->bg_color[2]);
			else
				shading(scene, &r, img->data[j][i]);
			++j;
		}
		++i;
	}
}
