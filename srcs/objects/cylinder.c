/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:04:06 by jhache            #+#    #+#             */
/*   Updated: 2018/05/17 13:52:40 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_math/vec2.h>
#include <float.h>
#include <math.h>
#include "rtv1.h"

/*
** cylinder_intersect: Calculates the distance between the intersection
**                     of the ray and the cylinder and the ray origin.
**
** -obj: the cylinder object
** -origin: the starting postion of the ray
** -u: the ray's unit vector
**
** returns: the distance, if an intersection point has been found.
**          Returns FLT_MAX otherwise.
*/

float				cylinder_intersect(t_object *obj, t_vec3f *origin,
		t_vec3f *u)
{
	float			a;
	float			b;
	float			c;
	float			delta;
	t_vec3f			tmp;

	vec3f_sub(origin, &obj->pos, &tmp);
	a = vec3f_dot_product(u, &obj->facing);
	a = vec3f_dot_product(u, u) - a * a;
	b = 2 * (vec3f_dot_product(u, &tmp)
			- vec3f_dot_product(u, &obj->facing)
			* vec3f_dot_product(&tmp, &obj->facing));
	c = vec3f_dot_product(&tmp, &tmp)
		- pow(vec3f_dot_product(&tmp, &obj->facing), 2)
		- obj->props.cylinder.radius * obj->props.cylinder.radius;
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

/*
** cylinder_normal: Computes the normal vector at the intersection point.
**
** formula:
** ph (vector) = hitpos - objpos
** hit_height = ph . axis
** h_pos = hit_height * axis
** normal = (hitpos - h_pos) normalized.
**
** normal = hitpos - ((hitpos - objpos) . axis) * axis [normalized]
*/

void				cylinder_normal(t_object *o, t_rt_result *r)
{
	t_vec3f			ph;
	t_vec3f			h_pos;

	vec3f_sub(&r->pos, &o->pos, &ph);
	vec3f_add(vec3f_mul(&o->facing,
				vec3f_dot_product(&ph, &o->facing), &h_pos),
			&o->pos, &h_pos);
	vec3f_normalize(vec3f_sub(&r->pos, &h_pos, &r->normal), &r->normal);
}

int					cylinder_init(t_object *object, const t_json_object *data)
{
	return (float_from_json(json_obj_get(data, "radius"),
				&object->props.cylinder.radius));
}
