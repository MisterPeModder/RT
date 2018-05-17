/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:23:09 by jhache            #+#    #+#             */
/*   Updated: 2018/05/17 12:51:32 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_math/vec2.h>
#include <float.h>
#include <math.h>
#include "rtv1.h"

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
	float			i[3];
	float			delta;
	t_vec3f			tmp;

	vec3f_sub(origin, &obj->pos, &tmp);
	i[2] = cos(obj->props.cone.opening_angle);
	i[2] *= i[2];
	i[0] = pow(vec3f_dot_product(u, &obj->facing), 2) - i[2];
	i[1] = 2 * (vec3f_dot_product(u, &obj->facing)
			* vec3f_dot_product(&tmp, &obj->facing)
			- vec3f_dot_product(u, &tmp) * i[2]);
	i[2] = vec3f_dot_product(&tmp, &obj->facing)
		* vec3f_dot_product(&tmp, &obj->facing)
		- vec3f_dot_product(&tmp, &tmp) * i[2];
	delta = i[1] * i[1] - 4 * i[0] * i[2];
	if (delta < 0)
		return (FLT_MAX);
	else if (delta == 0)
		return (-i[1] / (2 * i[0]));
	i[2] = (-i[1] - sqrt(delta)) / (2 * i[0]);
	i[0] = (-i[1] + sqrt(delta)) / (2 * i[0]);
	i[2] = i[2] > i[0] ? i[0] : i[2];
	return (i[2]);
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
	object->release = NULL;
	object->intersect = &cone_intersect;
	object->normal = &cone_normal;
	if (!float_from_json(json_obj_get(data, "opening_angle"),
				&object->props.cone.opening_angle) ||
			object->props.cone.opening_angle <= 0 ||
			object->props.cone.opening_angle >= 90)
		return (0);
	object->props.cone.opening_angle *= M_PI / 180;
	return (1);
}
