/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 23:16:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/11 21:21:24 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "rtv1.h"

#include <stdio.h>

float				sphere_intersect(t_object *obj, t_vec3f *origin, t_vec3f *u)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	t_vec3f	tmp;

	a = vec3f_dot_product(u, u);
	b = 2 * vec3f_dot_product(u, vec3f_sub(origin, &obj->pos, &tmp));
	c = vec3f_dot_product(vec3f_sub(origin, &obj->pos, &tmp), &tmp)
		- obj->props.sphere.radius * obj->props.sphere.radius;
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

int					sphere_init(t_object *object, const t_json_object *data)
{
	object->release = NULL;
	object->intersect = &sphere_intersect;
	object->normal = &sphere_normal;
	return (float_from_json(json_obj_get(data, "radius"),
				&object->props.sphere.radius) &&
			object->props.sphere.radius > 0);
}

void				sphere_normal(t_object *o, t_rt_result *r)
{
	vec3f_normalize(vec3f_sub(&r->pos, &o->pos, &r->normal), &r->normal);
}
