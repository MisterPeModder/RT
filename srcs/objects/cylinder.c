/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:04:06 by jhache            #+#    #+#             */
/*   Updated: 2018/05/14 15:45:26 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_math/vec2.h>
#include <float.h>
#include <math.h>
#include "rtv1.h"

/*
** cylidner_intersect: Calculates the distance between the intersection!!!!!!!!!!!!
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

float				cylinder_intersect(t_object *obj, t_vec3f *origin, t_vec3f *u)
{
	float			a;
	float			b;
	float			c;
	float			delta;
	t_vec3f			tmp;

	vec3f_sub(origin, &obj->pos, &tmp);
	a = vec3f_dot_product(u, u) - vec3f_dot_product(u, &obj->props.cylinder.axis) * vec3f_dot_product(u, &obj->props.cylinder.axis);
	b = 2 * (vec3f_dot_product(u, &tmp) - vec3f_dot_product(u, &obj->props.cylinder.axis) * vec3f_dot_product(&tmp, &obj->props.cylinder.axis));
	c = vec3f_dot_product(&tmp, &tmp) - pow(vec3f_dot_product(&tmp, &obj->props.cylinder.axis), 2) - obj->props.cylinder.radius * obj->props.cylinder.radius;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (FLT_MAX);
	else if (delta == 0)
		return (-b / (2 * a));
	c = (-b - sqrt(delta)) / (2 * a);
	a = (-b + sqrt(delta)) / (2 * a);
	c = c > a ? a : c;
	return (c);
}

void				cylinder_normal(t_object *o, t_rt_result *r)
{
	r->normal = o->pos;
	r->normal.y = r->pos.y;
	rotate_x(&r->normal, o->angle.x);
	rotate_y(&r->normal, o->angle.y);
	rotate_z(&r->normal, o->angle.z);
	vec3f_normalize(vec3f_sub(&r->pos, &r->normal, &r->normal), &r->normal);
}

int					cylinder_init(t_object *object, const t_json_object *data)
{
	object->release = NULL;
	object->intersect = &cylinder_intersect;
	object->normal = &cylinder_normal;
	vec3f_fill(&object->props.cylinder.axis, 0, 1, 0);
	rotate_x(&object->props.cylinder.axis, object->angle.x);
	rotate_y(&object->props.cylinder.axis, object->angle.y);
	rotate_z(&object->props.cylinder.axis, object->angle.z);
	if (!float_from_json(json_obj_get(data, "radius"),
						&object->props.cylinder.radius))
		return (0);
	return (1);
}
