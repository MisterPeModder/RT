/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:23:09 by jhache            #+#    #+#             */
/*   Updated: 2018/05/11 21:08:17 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_math/vec2.h>
#include <float.h>
#include <math.h>
#include "rtv1.h"

#include <stdio.h>

float				cone_intersect(t_object *obj, t_vec3f *origin, t_vec3f *u)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	t_vec3f	tmp;

	vec3f_sub(origin, &obj->pos, &tmp);
	c = cos(obj->props.cone.opening_angle * M_PI / 180)
		* cos(obj->props.cone.opening_angle * M_PI / 180);
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
//	t_real	m;
//	t_real	k;
	t_vec3f	normal;
	t_vec2f	tmp;

/*	m = dot_product(r->VECT_DIR, rt->curr_obj->vec) * r->LEN*//* + dot_product(rt->cam->pos*//* - p*//*, rt->curr_obj->vec)*//*;
	k = vec3f_norm(vec3f_sub(r->pos, vec3f_add(o->pos, vec3f_mult(o->props.cone.axis, m, &normal), &normal), &normal)) / m;
	vec3f_normalize(vec3f_sub(r->pos, vec3f_add(o->pos, vec3f_mult(o->props.cone.axis, m * (1 + k * k), &normal), &normal), &normal), &normal);*/
	vec2f_fill(&tmp, r->pos.x, r->pos.y);
	vec3f_cpy(&r->pos, &normal);
	normal.z = vec2f_norm(&tmp) * sin(o->props.cone.opening_angle * M_PI / 180);
	vec3f_normalize(&normal, &normal);
	r->normal = normal;
}

int					cone_init(t_object *object, const t_json_object *data)
{
	t_vec3f	*ptr;

	object->release = NULL;
	object->intersect = &cone_intersect;
	object->normal = &cone_normal;
	ptr = &object->props.cone.axis;
	vec3f_fill(ptr, 0, 1, 0);
//	APPLY ROTATION HERE
	return (float_from_json(json_obj_get(data, "opening_angle"),
				&object->props.cone.opening_angle) &&
			object->props.cone.opening_angle > 0 &&
			object->props.cone.opening_angle < 90);
}
