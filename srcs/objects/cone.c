/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:23:09 by jhache            #+#    #+#             */
/*   Updated: 2018/05/29 01:51:45 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

int					cone_init(t_object *object, const t_json_object *data)
{
	if (!float_from_json(json_obj_get(data, "opening_angle"),
				&object->props.cone.opening_angle) ||
			object->props.cone.opening_angle <= 0 ||
			object->props.cone.opening_angle >= 90)
		return (0);
	object->props.cone.opening_angle *= M_PI / 180;
	return (1);
}
