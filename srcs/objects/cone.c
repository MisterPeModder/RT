/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:23:09 by jhache            #+#    #+#             */
/*   Updated: 2018/05/12 17:31:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_math/vec2.h>
#include <float.h>
#include <math.h>
#include "rtv1.h"

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
	a = pow(vec3f_dot_product(u, &obj->props.cone.axis), 2) - c;
	b = 2 * (vec3f_dot_product(u, &obj->props.cone.axis)
			* vec3f_dot_product(&tmp, &obj->props.cone.axis)
			- vec3f_dot_product(u, &tmp) * c);
	c = vec3f_dot_product(&tmp, &obj->props.cone.axis)
		* vec3f_dot_product(&tmp, &obj->props.cone.axis)
		- vec3f_dot_product(&tmp, &tmp) * c;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (FLT_MAX);
	else if (delta == 0)
		c = -b / (2 * a);
	else
	{
		c = (-b - sqrt(delta)) / (2 * a);
		a = (-b + sqrt(delta)) / (2 * a);
		c = c > a ? a : c;
	}
	return (c);
}


void				cone_normal(t_object *o, t_rt_result *r)
{
	t_vec3f			vs;
	t_vec3f			n;
	float			s;
	t_vec3f			v;

	s = vec3f_norm(vec3f_sub(&r->pos, &o->pos, &vs));
	n = o->props.cone.axis;
	if (vec3f_dot_product(&o->props.cone.axis, &vs) < 0)
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
	vec3f_fill(&object->props.cone.axis, 0, 1, 0);
	rotate_x(&object->props.cone.axis, object->angle.x);
	rotate_y(&object->props.cone.axis, object->angle.y);
	rotate_z(&object->props.cone.axis, object->angle.z);
	if (!float_from_json(json_obj_get(data, "opening_angle"),
				&object->props.cone.opening_angle) &&
			object->props.cone.opening_angle <= 0 &&
			object->props.cone.opening_angle >= 90)
		return (0);
	object->props.cone.opening_angle *= M_PI / 180;
	return (1);
}
