/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 12:54:56 by jloro             #+#    #+#             */
/*   Updated: 2018/05/31 12:56:03 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "rt.h"

void				cone_normal(t_object *o, t_rt_result *r)
{
	t_vec3f			vs;
	t_vec3f			n;
	float			s;
	t_vec3f			v;

	if (o->props.cone.face == 0)
	{
		s = vec3f_norm(vec3f_sub(&r->pos, &o->pos, &vs));
		n = o->facing;
		if (vec3f_dot_product(&o->facing, &vs) < 0)
			vec3f_neg(&n, &n);
		vec3f_mul(&n, s / cos(o->props.cone.opening_angle), &v);
		vec3f_add(&o->pos, &v, &v);
		vec3f_normalize(vec3f_sub(&r->pos, &v, &v), &r->normal);
	}
	else if (o->props.cone.face == 1)
		vec3f_neg(&o->facing, &r->normal);
	else
		r->normal = o->facing;
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
	if (!bool_from_json(json_obj_get(data, "simple"),
				&object->props.cone.simple))
		return (0);
	if (float_from_json(json_obj_get(data, "length"),
				&object->props.cone.len))
	{
		if (object->props.cone.len <= 0)
			return (0);
	}
	else
		object->props.cone.len = -1;
	return (1);
}
