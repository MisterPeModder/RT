/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 13:14:20 by jloro             #+#    #+#             */
/*   Updated: 2018/06/07 15:14:11 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*
** POINT 5 6 7 8
*/

static int					cube_init3(t_object *object)
{
	t_clfloat3		tmp;

	vec3cl_sub(&object->facing, &object->dir, &tmp);
	vec3cl_add(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.cube.len, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.cube.p[4]);
	vec3cl_neg(&object->facing, &tmp);
	vec3cl_sub(&tmp, &object->dir, &tmp);
	vec3cl_add(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.cube.len, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.cube.p[5]);
	vec3cl_neg(&object->facing, &tmp);
	vec3cl_sub(&tmp, &object->dir, &tmp);
	vec3cl_sub(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.cube.len, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.cube.p[6]);
	vec3cl_sub(&object->facing, &object->dir, &tmp);
	vec3cl_sub(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.cube.len, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.cube.p[7]);
	return (1);
}

/*
** POINT 1 2 3 4
*/

static int					cube_init2(t_object *object)
{
	t_clfloat3		tmp;

	vec3cl_add(&object->facing, &object->dir, &tmp);
	vec3cl_sub(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.cube.len, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.cube.p[0]);
	vec3cl_add(&object->facing, &object->dir, &tmp);
	vec3cl_add(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.cube.len, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.cube.p[1]);
	vec3cl_neg(&object->facing, &tmp);
	vec3cl_add(&tmp, &object->dir, &tmp);
	vec3cl_add(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.cube.len, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.cube.p[2]);
	vec3cl_neg(&object->facing, &tmp);
	vec3cl_add(&tmp, &object->dir, &tmp);
	vec3cl_sub(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.cube.len, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.cube.p[3]);
	return (cube_init3(object));
}

int					cube_init(t_object *object, const t_json_object *data)
{
	if (!float_from_json(json_obj_get(data, "length"),
				&object->props.cube.len) || object->props.cube.len <= 0)
		return (0);
	return (cube_init2(object));
}
