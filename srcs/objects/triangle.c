/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 14:27:00 by jloro             #+#    #+#             */
/*   Updated: 2018/06/21 17:42:32 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#include <stdio.h>

int					triangle_init(t_object *object, const t_json_object *data)
{
	t_clfloat3		u;
	t_clfloat3		v;

	if (!vec3f_from_json(json_obj_get(data, "pos1"),
				&object->props.triangle.pos1))
		return (0);
	if (!vec3f_from_json(json_obj_get(data, "pos2"),
				&object->props.triangle.pos2))
		return (0);
	vec3cl_sub(&object->props.triangle.pos2, &object->props.triangle.pos1, &u);
	vec3cl_sub(&object->pos, &object->props.triangle.pos1, &v);
	object->facing.x = u.y * v.z - u.z * v.y;
	object->facing.y = u.z * v.x - u.x * v.z;
	object->facing.z = u.x * v.y - u.y * v.x;
	vec3cl_normalize(&object->facing, &object->facing);
	return (1);
}
