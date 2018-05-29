/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:02:22 by jloro             #+#    #+#             */
/*   Updated: 2018/05/29 14:25:58 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "rt.h"

float				disk_intersect(t_object *obj, t_vec3f *origin,
		t_vec3f *u)
{
	float			l_dot_n;
	t_vec3f			tmp;
	t_vec3f			p;
	float			t;

	if (vec3f_dot_product(u, &obj->facing) > 0)
		vec3f_neg(&obj->facing, &obj->facing);
	if (fabs(l_dot_n = vec3f_dot_product(u, &obj->facing)) < 1e-6)
		return (FLT_MAX);
	t = vec3f_dot_product(vec3f_sub(&obj->pos, origin, &tmp),
				&obj->facing) / l_dot_n;
	vec3f_add(origin, vec3f_mul(u, t, &tmp), &p);
	if (vec3f_dot_product(vec3f_sub(&p, &obj->pos, &tmp),
			vec3f_sub(&p, &obj->pos, &tmp)) <= obj->props.sphere.radius
			* obj->props.sphere.radius)
		return (t);
	return (FLT_MAX);
}

int					disk_init(t_object *object, const t_json_object *data)
{
	object->release = NULL;
	object->intersect = &disk_intersect;
	object->normal = &plane_normal;
	return (float_from_json(json_obj_get(data, "radius"),
				&object->props.sphere.radius) &&
			object->props.sphere.radius > 0);
}
