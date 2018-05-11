/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 23:16:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/11 14:31:18 by yguaye           ###   ########.fr       */
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
	float	d;

	a = u->x * u->x + u->y * u->y + u->z * u->z;
	b = 2 * (u->x * (origin->x - obj->pos.x)
			+ u->y * (origin->y - obj->pos.y)
			+ u->z * (origin->z - obj->pos.z));
	c = ((origin->x - obj->pos.x) * (origin->x - obj->pos.x)
			+ (origin->y - obj->pos.y) * (origin->y - obj->pos.y)
			+ (origin->z - obj->pos.z) * (origin->z - obj->pos.z))
		- obj->props.sphere.radius * obj->props.sphere.radius;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (FLT_MAX);
	else if (delta == 0)
		d = -b / (2 * a);
	else
	{
		d = (-b - sqrt(delta)) / (2 * a);
		c = (-b + sqrt(delta)) / (2 * a);
		d = d > c ? c : d;
	}
	return (d);
}

void				sphere_normal(t_object *o, const t_vec3f *hit, t_vec3f *r)
{
	vec3f_normalize(vec3f_sub(hit, &o->pos, r), r);
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
