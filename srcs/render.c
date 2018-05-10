/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 12:32:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 19:09:11 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <math.h>
#include "rtv1.h"

#include <stdio.h>

/*
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
   dprintf(2, "hit at (%f, %f, %f)\n", r->pos.x, r->pos.y, r->pos.z);
   }*/

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
	t_hitlst		*hits;
	t_hitlst		*tmp;

	i = 0;
	hits = NULL;
	while (i < scene->objs_num)
	{
		hits = hitlstjoin(hits, scene->objs[i].intersect(
					&scene->objs[i], o, u));
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
/*
   void		sphere_shading(t_rt *rt, t_3dpt vect_dir, const t_real t, int *pixel)
   {
   int		k;
   t_color	clr_tmp;
   t_3dpt	light_vector;
   t_3dpt	point_coor;
   t_real	light_power;
   t_obj	*obj_tmp;
   t_light	*light_tmp;

 *pixel = 0;
 light_tmp = rt->light;
 point_coor = scalar_mult(vect_dir, t);
 while (light_tmp != NULL)
 {
 light_vector = normalize_vector(substract_vector(light_tmp->pos, point_coor));
 obj_tmp = rt->first_obj;
 if (compute_t(&obj_tmp, point_coor, light_vector) == -1)
 {
 light_power = dot_product(light_vector, normalize_vector(
						substract_vector(point_coor, rt->curr_obj->coord)));//le substract_vector correspond a la normale de la sphere. ce serai bien de la calculer en dehors de la boucle, comme pour le cone
						k = -1;
						while (++k < 3)
						clr_tmp.byte[k] = rt->curr_obj->clr.byte[k]
 * rt->curr_obj->mat.diffuse_color * light_power;
 clr_tmp.byte[3] = 0;
 if (light_power >= 0)
 add_color_to_pixel(pixel, clr_tmp);
 }
 light_tmp = light_tmp->next;
 }
 }*/

//CONVERTED
static void			shading(t_scene *scene, t_rt_result *r, t_color c)
{
	size_t			i;
	t_vec3f			lvec;
	t_rt_result		sink;
	float			power;

	i = 0;
	while (i < scene->lights_num)
	{
		vec3f_normalize(vec3f_sub(&scene->lights[i], &r->pos, &lvec), &lvec);
		if (!get_hitpos(scene, &r->pos, &lvec, &sink))
		{
			power = vec3f_dot_product(&lvec, &r->normal);
			c[0] = r->obj->color[0] * r->obj->brightness * power;
			c[1] = r->obj->color[1] * r->obj->brightness * power;
			c[2] = r->obj->color[2] * r->obj->brightness * power;
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
			if (get_hitpos(scene, &scene->cam.pos, &unit, &r))
				color_fill(img->data[j++][i], scene->bg_color[0], scene->bg_color[1], scene->bg_color[2]);
			else
				shading(scene, &r, img->data[j++][i]);
		}
		++i;
	}
}
