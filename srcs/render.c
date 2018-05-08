/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:32:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/08 12:36:27 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <math.h>
#include "rtv1.h"

static int			get_hitpos(t_scene *scene, t_vec3f *u, t_rt_result *r)
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

static void			set_color(t_scene *scene, t_rt_result *r, t_color c)
{
	float			brightness;
	t_vec3f			light;
	t_vec3f			dir;

	vec3f_fill(&light, 10, -5, -5);
	vec3f_normalize(vec3f_sub(&r->pos, &light, &dir), &dir);
	brightness = vec3f_dot_product(&r->normal, &dir);
	color_brightness(c, r->obj->color, brightness);
	(void)scene;
}

int					render_frame(t_scene *scene, t_img *img)
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
					(2.f * ((float)x + .5f) / (float)img->w - 1) * coefs[0] * coefs[1],
					(1 - 2.f * ((float)y + .5f) / (float)img->h) * coefs[0],
					-1.f);
			vec3f_normalize(&unit, &unit);
			if (!get_hitpos(scene, &unit, &r))
				color_fill(img->data[x][y++], scene->bg_color[0], scene->bg_color[1], scene->bg_color[2]);
			else
				set_color(scene, &r, img->data[x][y++]);
		}
		++x;
	}
	return (1);
}
