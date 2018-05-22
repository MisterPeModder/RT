/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:01:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/22 19:10:15 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include "rt.h"

static int			obj_props(t_object *obj, char *str,
		const t_json_object *data, t_obj_class *types)
{
	int				i;

	i = 0;
	while (i < OBJ_TYPES_COUNT)
	{
		if (ft_strequ(str, types[i].name))
		{
			obj->type = &types[i];
			return (!obj->type->construct || obj->type->construct(obj, data));
		}
		++i;
	}
	return (0);
}

static int			calc_angle(t_object *object, const t_json_value *v)
{
	t_vec3f			angle;

	if (!v)
		vec3f_fill(&angle, 0, 0, 0);
	else if (!angle_from_json(v, &angle))
		return (0);
	vec3f_fill(&object->facing, 0, 1, 0);
	rotate_x(&object->facing, angle.x);
	rotate_y(&object->facing, angle.y);
	rotate_z(&object->facing, angle.z);
	return (1);
}

int					obj_make(t_object *object, t_obj_class *types,
		const t_json_object *data)
{
	t_json_value	*tmp;

	if (!vec3f_from_json(json_obj_get(data, "pos"), &object->pos) ||
			!calc_angle(object, json_obj_get(data, "angle")))
		return (0);
	if ((tmp = json_obj_get(data, "color")))
	{
		if (!color_from_json(tmp, &object->color))
			return (0);
	}
	else
		vec3f_fill(&object->color, 1, 1, 1);
	if (!(tmp = json_obj_get(data, "type")) || tmp->str.type != JSON_STRING ||
			!obj_props(object, tmp->str.value, data, types))
		return (0);
	return (1);
}
