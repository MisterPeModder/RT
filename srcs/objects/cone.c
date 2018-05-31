/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:23:09 by jhache            #+#    #+#             */
/*   Updated: 2018/05/31 12:56:16 by jloro            ###   ########.fr       */
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
	float			i[4];
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
	i[3] = i[1] * i[1] - 4 * i[0] * i[2];
	if (i[3] < 0)
		return (FLT_MAX);
	else if (i[3] == 0)
		return (-i[1] / (2 * i[0]));
	i[2] = (-i[1] - sqrt(i[3])) / (2 * i[0]);
	i[0] = (-i[1] + sqrt(i[3])) / (2 * i[0]);
	i[2] = i[2] > i[0] ? i[0] : i[2];
	i[1] = vec3f_dot_product(u, &obj->facing) * (i[0] > 0 ? i[0] : i[2]) +
		vec3f_dot_product(vec3f_sub(origin, &obj->pos, &tmp), &obj->facing);
	return (cone_intersect2(obj, origin, u, i));
}

float				cone_intersect2(t_object *obj, t_vec3f *origin,
		t_vec3f *u, float i[4])
{
	obj->props.cone.face = 0;
	if (obj->props.cone.simple)
	{
		if (i[1] > 0)
			return (FLT_MAX);
		if (obj->props.cone.simple && obj->props.cone.len != -1 &&
					i[1] < 0 - obj->props.cone.len)
			return (cone_intersect_simple(obj, origin, u));
		return (i[0] > 0 ? i[0] : i[2]);
	}
	else
	{
		if (obj->props.cone.len == -1)
			return (i[0] > 0 ? i[0] : i[2]);
		if (i[1] < 0 - obj->props.cone.len / 2 ||
				i[1] > obj->props.cone.len / 2)
		{
			if ((i[3] = cone_intersect_double(obj, origin, u, 1)) != FLT_MAX)
				return (i[3]);
			if ((i[3] = cone_intersect_double(obj, origin, u, 2)) != FLT_MAX)
				return (i[3]);
			return (FLT_MAX);
		}
		return (i[0] > 0 ? i[0] : i[2]);
	}
}

float				cone_intersect_simple(t_object *obj, t_vec3f *origin,
		t_vec3f *u)
{
	float	delta;
	t_vec3f	tmp;
	t_vec3f	tmp2;
	t_vec3f	tmp3;

	vec3f_sub(&obj->pos, vec3f_mul(&obj->facing, obj->props.cone.len
		, &tmp2), &tmp3);
	delta = vec3f_dot_product(vec3f_sub(&tmp3, origin, &tmp),
			&obj->facing) / vec3f_dot_product(u, &obj->facing);
	vec3f_add(origin, vec3f_mul(u, delta, &tmp2), &tmp);
	if (vec3f_dot_product(vec3f_sub(&tmp, &tmp3, &tmp2),
			vec3f_sub(&tmp, &tmp3, &tmp2)) <=
			pow(tan(obj->props.cone.opening_angle)
			* vec3f_norm(vec3f_sub(&tmp3, &obj->pos, &tmp)), 2))
	{
		obj->props.cone.face = 1;
		return (delta);
	}
	return (FLT_MAX);
}

float				cone_intersect_double(t_object *obj, t_vec3f *origin,
		t_vec3f *u, int i)
{
	t_vec3f			tmp;
	t_vec3f			tmp2;
	t_vec3f			tmp3;
	float			a;

	if (i == 2)
		vec3f_add(&obj->pos, vec3f_mul(&obj->facing, obj->props.cone.len
					/ 2, &tmp2), &tmp3);
	else if (i == 1)
		vec3f_sub(&obj->pos, vec3f_mul(&obj->facing, obj->props.cone.len
					/ 2, &tmp2), &tmp3);
	a = vec3f_dot_product(vec3f_sub(&tmp3, origin, &tmp),
			&obj->facing) / vec3f_dot_product(u, &obj->facing);
	vec3f_add(origin, vec3f_mul(u, a, &tmp2), &tmp);
	if (vec3f_dot_product(vec3f_sub(&tmp, &tmp3, &tmp2),
				vec3f_sub(&tmp, &tmp3, &tmp2)) <=
				pow(tan(obj->props.cone.opening_angle)
				* vec3f_norm(vec3f_sub(&tmp3, &obj->pos, &tmp)), 2))
	{
		obj->props.cone.face = i;
		return (a);
	}
	return (FLT_MAX);
}
