/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:33:31 by jloro             #+#    #+#             */
/*   Updated: 2018/06/08 12:17:03 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					pyramid_init(t_object *object, const t_json_object *data)
{
	t_clfloat3		tmp;

	if (!float_from_json(json_obj_get(data, "length"),
				&object->props.pyramid.len) || object->props.pyramid.len <= 0)
		return (0);
	if (!float_from_json(json_obj_get(data, "base length"),
				&object->props.pyramid.len_base)
				|| object->props.pyramid.len_base <= 0)
		return (0);
	//1
	vec3cl_sub(&object->dir, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.pyramid.len_base, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.pyramid.p[0]);
	//2
	vec3cl_add(&object->dir, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.pyramid.len_base, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.pyramid.p[1]);
	//3
	vec3cl_neg(&object->dir, &tmp);
	vec3cl_sub(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.pyramid.len_base, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.pyramid.p[2]);
	//4
	vec3cl_neg(&object->dir, &tmp);
	vec3cl_add(&tmp, &object->right, &tmp);
	vec3cl_mul(&tmp, object->props.pyramid.len_base, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.pyramid.p[3]);
	//SOMMET
	vec3cl_mul(&object->facing, object->props.pyramid.len, &tmp);
	vec3cl_add(&object->pos, &tmp, &object->props.pyramid.p[4]);
	return (1);
}
