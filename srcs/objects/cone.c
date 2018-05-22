/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:23:09 by jhache            #+#    #+#             */
/*   Updated: 2018/05/22 19:09:58 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_math/vec2.h>
#include <float.h>
#include <math.h>
#include "rt.h"

/*
** cone_intersect: Calculates the distance between the intersection
**                 of the ray and the cone and the ray origin.
**
** -obj: the cone object
** -origin: the starting postion of the ray
** -u: the ray's unit vector
**
** note: the i[] variable holds the a, b, and c parameters of the quadratic.
**
** returns: the distance, if an intersectection point has been found.
**          Returns FLT_MAX otherwise.
*/

float				cone_intersect(t_object *obj, t_vec3f *origin, t_vec3f *u)
{
	float			a;
	float			b;
	float			c;
	float			delta;
	t_vec3f			tmp;

	vec3f_sub(origin, &obj->pos, &tmp);
	c = cos(obj->props.cone.opening_angle);
	c *= c;
	a = pow(vec3f_dot_product(u, &obj->facing), 2) - c;
	b = 2 * (vec3f_dot_product(u, &obj->facing)
			* vec3f_dot_product(&tmp, &obj->facing)
			- vec3f_dot_product(u, &tmp) * c);
	c = vec3f_dot_product(&tmp, &obj->facing)
		* vec3f_dot_product(&tmp, &obj->facing)
		- vec3f_dot_product(&tmp, &tmp) * c;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (FLT_MAX);
	else if (delta == 0)
		return (-b / (2 * a));
	c = (-b - sqrt(delta)) / (2 * a);
	a = (-b + sqrt(delta)) / (2 * a);
	c = c > a ? a : c;
	return (a > 0 ? a : c);
}

void				cone_normal(t_object *o, t_rt_result *r)
{
	t_vec3f			vs;
	t_vec3f			n;
	float			s;
	t_vec3f			v;

	s = vec3f_norm(vec3f_sub(&r->pos, &o->pos, &vs));
	n = o->facing;
	if (vec3f_dot_product(&o->facing, &vs) < 0)
		vec3f_neg(&n, &n);
	vec3f_mul(&n, s / cos(o->props.cone.opening_angle), &v);
	vec3f_add(&o->pos, &v, &v);
	vec3f_normalize(vec3f_sub(&r->pos, &v, &v), &r->normal);
}

int					cone_init(t_object *object, const t_json_object *data)
{
	if (!float_from_json(json_obj_get(data, "opening_angle"),
				&object->props.cone.opening_angle) ||
			object->props.cone.opening_angle <= 0 ||
			object->props.cone.opening_angle >= 90)
		return (0);
	object->props.cone.opening_angle *= M_PI / 180;
	return (1);
}
