/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:01:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/17 12:08:12 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include "rtv1.h"

static int			obj_props(t_object *object, char *str,
		const t_json_object *data, t_obj_type *type)
{
	if (ft_strequ(str, "sphere") && (*type = OBJ_SPHERE))
		return (sphere_init(object, data));
	else if (ft_strequ(str, "cone") && (*type = OBJ_CONE))
		return (cone_init(object, data));
	else if (ft_strequ(str, "plane") && (*type = OBJ_PLANE))
		return (plane_init(object, data));
	else if (ft_strequ(str, "cylinder") && (*type = OBJ_CYLINDER))
		return (cylinder_init(object, data));
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

int					obj_make(t_object *object, const t_json_object *data)
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
			!obj_props(object, tmp->str.value, data, &object->type))
		return (0);
	return (1);
}

int					obj_release(t_object *obj)
{
	if (obj->release)
		(*obj->release)(obj);
	return (0);
}

int					objs_release(t_object *objs, size_t num)
{
	size_t			i;

	if (!objs)
		return (0);
	i = 0;
	while (i < num)
		obj_release(&objs[i++]);
	free(objs);
	return (0);
}
