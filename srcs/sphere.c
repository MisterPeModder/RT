/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 23:16:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/08 03:32:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

static int			solve_quadratic(float a, float b, float c, float *r)
{
	float			delta;
	float			tmp;

	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (0);
	else if (delta == 0)
	{
		r[0] = -0.5f * b / a;
		r[1] = r[0];
		return (1);
	}
	else
	{
		tmp = b > 0 ? -0.5f * (b + sqrt(delta)) : -0.5f * (b - sqrt(delta));
		r[0] = tmp / a;
		r[1] = c / tmp;
	}
	if (r[0] > r[1])
	{
		tmp = r[0];
		r[0] = r[1];
		r[1] = tmp;
	}
	return (2);
}

t_hitlst			*sphere_intersect(t_object *o, t_vec3f *cam, t_vec3f *u)
{
	float			r[2];
	float			n[3];
	t_vec3f			l;
	int				ret;
	t_hitlst		*lst;

	vec3f_sub(cam, &o->pos, &l);
	n[0] = vec3f_dot_product(u, u);
	n[1] = 2 * vec3f_dot_product(u, &l);
	n[2] = vec3f_dot_product(&l, &l) - o->props.sphere.radius *
		o->props.sphere.radius;
	if (!(ret = solve_quadratic(n[0], n[1], n[2], r)))
		return (NULL);
	if (r[0] < 0)
	{
		ret = 1;
		if ((r[0] = r[1]) < 0)
			return (NULL);
	}
	vec3f_fill(&l, 0, 0, 0);
	if (ret == 1)
		return (hitlstnew(o, r[0], &l, &l));
	lst = hitlstnew(o, r[0], &l, &l);
	if (lst)
		lst->next = hitlstnew(o, r[1], &l, &l);
	return (lst);
}

/*
   t_hitlst			*sphere_intersect(t_object *o, t_vec3f *cam, t_vec3f *u)
   {
   float			delta;
   t_vec3f			v[3];
   float			i[2];
   t_hitlst		*lst;

   i[0] = vec3f_dot_product(u, vec3f_sub(cam, &o->pos, v));
   i[1] = vec3f_norm(v);
   delta = i[0] * i[0] - i[1] * i[1] +
   o->props.sphere.radius * o->props.sphere.radius;
   if (delta < 0)
   return (NULL);
   if (delta == 0)
   lst = hitlstnew(o, -i[0], vec3f_mul(v, -i[0], &v[1]),
   vec3f_sub(v, &o->pos, &v[2]));
   else if (delta > 0)
   {
   i[1] = (float)sqrt(delta);
   lst = hitlstnew(o, -i[0] + i[1], vec3f_mul(v, -i[0] + i[1], &v[1]),
   vec3f_sub(v, &o->pos, &v[2]));
   if (lst)
   lst->next = hitlstnew(o, -i[0] - i[1], vec3f_mul(
   v, -i[0] - i[1], &v[1]), vec3f_sub(v, &o->pos, &v[2]));
   }
   return (lst);
   }
*/

int					sphere_init(t_object *object, const t_json_object *data)
{
	object->release = NULL;
	object->intersect = &sphere_intersect;
	return (float_from_json(json_obj_get(data, "radius"),
				&object->props.sphere.radius) &&
			object->props.sphere.radius > 0);
}
