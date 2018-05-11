/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:01:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/11 18:30:48 by jhache           ###   ########.fr       */
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
	/*else if (ft_strequ(str, "plane") && (*type = OBJ_PLANE))
		return (plane_init(object, data));*/
	return (0);
}

static int			obj_make2(t_object *object, const t_json_object *data)
{
	t_json_value	*tmp;

	if ((tmp = json_obj_get(data, "brightness")))
	{
		if (!float_from_json(tmp, &object->brightness))
			return (0);
	}
	else
		object->brightness = 0.5f;
	return (1);
}

int					obj_make(t_object *object, const t_json_object *data)
{
	t_json_value	*tmp;

	if (!vec3f_from_json(json_obj_get(data, "pos"), &object->pos))
		return (0);
	if ((tmp = json_obj_get(data, "angle")))
	{
		if (!angle_from_json(tmp, &object->angle))
			return (0);
	}
	else
		vec3f_fill(&object->angle, 0, 0, 0);
	if ((tmp = json_obj_get(data, "color")))
	{
		if (!color_from_json(tmp, object->color))
			return (0);
	}
	else
		color_fill(object->color, 255, 255, 255);
	if (!(tmp = json_obj_get(data, "type")) || tmp->str.type != JSON_STRING ||
			!obj_props(object, tmp->str.value, data, &object->type))
		return (0);
	return (obj_make2(object, data));
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
