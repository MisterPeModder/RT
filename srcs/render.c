/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:32:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/12 15:22:11 by jhache           ###   ########.fr       */
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
	r->obj->normal(r->obj, r);
	return (1);
}

//CONVERTED
static void			shading(t_scene *scene, t_rt_result *r, t_color c)
{
	size_t			i;
	t_vec3f			lvec;
	t_rt_result		sink;
	t_vec3f			start;
	float			component[2];

	i = 0;
	color_fill(c, 0, 0, 0);//c'est ici que doit etre initialiser la composante Ambient du shading. a (0, 0, 0), elle est desactive.
	while (i < scene->lights_num)
	{
		vec3f_normalize(vec3f_sub(&scene->lights[i], &r->pos, &lvec), &lvec);
//		vec3f_add(&r->pos, vec3f_mul(&lvec, 0.0001, &start), &start);
		start = r->pos;
		if (!get_hitpos(scene, &start, &lvec, &sink))
		{
			component[0] = 0.25 * vec3f_dot_product(&lvec, &r->normal);
			component[1] = vec3f_dot_product(&r->normal, &lvec);
			if (component[1] < 0)
				component[1] = 0;
			component[1] = pow(vec3f_dot_product(vec3f_sub(
							vec3f_mul(&r->normal, 2 * component[1], &start),
							&r->normal, &start), &lvec), 60) * 0.25;
//			dprintf(2, "power: %.4f\n", component[1]);
			colorize(c, r->obj->color, component);
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
