/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:23:09 by jhache            #+#    #+#             */
/*   Updated: 2018/08/20 01:16:49 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

int					cone_init(t_object *object, const t_json_object *data)
{
	t_json_value	*tmp;

	if (!float_from_json(json_obj_get(data, "opening_angle"),
				&object->props.cone.opening_angle)
			|| object->props.cone.opening_angle <= 0
			|| object->props.cone.opening_angle >= 90)
		return (0);
	object->props.cone.opening_angle *= M_PI / 180;
	if ((tmp = json_obj_get(data, "simple")))
	{
		if (!bool_from_json(tmp, &object->props.cone.simple))
			return (0);
	}
	else
		object->props.cone.simple = 0;
	if ((tmp = json_obj_get(data, "length")))
	{
		if (!float_from_json(tmp, &object->props.cone.len)
				|| object->props.cone.len <= 0)
			return (0);
	}
	else
		object->props.cone.len = -1;
	return (1);
}
