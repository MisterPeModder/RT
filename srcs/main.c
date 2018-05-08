/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/08 04:27:00 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <libft_base/io.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "rtv1.h"

#include <stdio.h>

int					get_hitpos(t_scene *scene, t_vec3f *u, t_rt_result *r)
{
	size_t			i;
	t_hitlst		*hits;
	t_hitlst		*tmp;

	i = 0;
	hits = NULL;
	while (i < scene->objs_num)
	{
		hits = hitlstjoin(hits, scene->objs[i].intersect(
					&scene->objs[i], &scene->cam.pos, u));
		++i;
	}
	tmp = hits;
	i = 0;
	while (tmp)
	{
		if (!i || r->dist > tmp->r.dist)
			ft_memcpy(r, &tmp->r, sizeof(t_rt_result));
		i = 1;
		tmp = tmp->next;
	}
	hitlstdel(hits);
	return (hits ? 1 : 0);
}

int					draw_frame(t_scene *scene, t_img *img)
{
	unsigned int	x;
	unsigned int	y;
	t_vec3f			unit;
	t_rt_result		r;
	float			coefs[2];

	x = 0;
	coefs[0] = tan(scene->cam.fov * 0.5);
	coefs[1] = (float)img->w / (float)img->h;
	while (x < img->w)
	{
		y = 0;
		while (y < img->h)
		{
			vec3f_fill(&unit,
					2.f * ((float)x + .5f) / (float)img->w - 1 * coefs[0] * coefs[1],
					1 - 2.f * ((float)y + .5f) / (float)img->h * coefs[0],
					-1.f);
			vec3f_normalize(&unit, &unit);
			if (!get_hitpos(scene, &unit, &r))
				color_fill(img->data[x][y++], scene->bg_color[0], scene->bg_color[1], scene->bg_color[2]);
			else
				color_fill(img->data[x][y++], r.obj->color[0], r.obj->color[1],
						r.obj->color[2]);
		}
		++x;
	}
	return (1);
}

int					main(int argc, char **argv)
{
	t_img			*img;
	t_scene			scene;

	if (argc != 2)
	{
		ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
		return (-1);
	}
	if (!(img = img_make(320, 180)) || !scene_parse(&scene, argv[1]))
	{
		img_release(&img);
		return (-2);
	}
	if (!draw_frame(&scene, img))
	{
		objs_release(scene.objs, scene.objs_num);
		img_release(&img);
		return (-3);
	}
	img_output(img);
	objs_release(scene.objs, scene.objs_num);
	img_release(&img);
	return (0);
}
