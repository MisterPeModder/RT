/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:32:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 17:20:13 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <math.h>
#include "rtv1.h"

#include <stdio.h>

static void			set_color(t_scene *scene, t_rt_result *r, t_color c)
{
	float			brightness;
	t_vec3f			light;
	t_vec3f			dir;

	vec3f_fill(&light, 1, 10, 0);
	vec3f_normalize(vec3f_sub(&r->pos, &light, &dir), &dir);
	brightness = vec3f_dot_product(&r->normal, &dir);
	color_brightness(c, r->obj->color, brightness);
	(void)scene;
}

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
			if (get_hitpos(scene, &unit, &r))
				color_fill(img->data[j++][i], scene->bg_color[0], scene->bg_color[1], scene->bg_color[2]);
			else
				set_color(scene, &r, img->data[j++][i]);
		}
		++i;
	}
}
