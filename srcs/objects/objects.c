/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:01:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/20 04:46:36 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include "rt.h"

static int			obj_props(t_object *object, char *str,
		const t_json_object *data, t_obj_type *type)
{
	if (ft_strequ(str, "sphere") && (*type = OBJ_SPHERE))
		return (sphere_init(object, data));
	else if (ft_strequ(str, "cone") && (*type = OBJ_CONE))
		return (cone_init(object, data));
	else if (ft_strequ(str, "plane") && (*type = OBJ_PLANE))
		return (1);
	else if (ft_strequ(str, "cylinder") && (*type = OBJ_CYLINDER))
		return (cylinder_init(object, data));
	else if (ft_strequ(str, "disk") && (*type = OBJ_DISK))
		return (disk_init(object, data));
	else if (ft_strequ(str, "triangle") && (*type = OBJ_TRIANGLE))
		return (triangle_init(object, data));
	else if (ft_strequ(str, "paraboloid") && (*type = OBJ_PARABOLOID))
		return (paraboloid_init(object, data));
	else if ((ft_strequ(str, "mesh") || ft_strequ(str, "wavefront_obj"))
			&& (*type = OBJ_MESH))
		return ((object->props.mesh.is_wobj = ft_strequ(str, "wavefront_obj"))
				+ 1);
	return (0);
}

static int			calc_angle(t_object *object, const t_json_value *v)
{
	cl_float3			angle;

	if (!v)
		vec3cl_fill(&angle, 0, 0, 0);
	else if (!angle_from_json(v, &angle))
		return (0);
	vec3cl_fill(&object->facing, 0, 1, 0);
	rotate_x(&object->facing, angle.x);
	rotate_y(&object->facing, angle.y);
	rotate_z(&object->facing, angle.z);
	vec3cl_fill(&object->dir, 0, 0, 1);
	rotate_x(&object->dir, angle.x);
	rotate_y(&object->dir, angle.y);
	rotate_z(&object->dir, angle.z);
	vec3cl_fill(&object->right, 1, 0, 0);
	rotate_x(&object->right, angle.x);
	rotate_y(&object->right, angle.y);
	rotate_z(&object->right, angle.z);
	return (1);
}

static void			obj_default_material(t_object *object)
{
	object->mat.props = MAT_NONE;
	object->mat.props_coef = 0.f;
	object->mat.refractive_index = 1.f;
}

int					obj_make(t_scene *scene, t_object *object,
		const t_json_object *data)
{
	t_json_value	*tmp;

	if (!vec3f_from_json(json_obj_get(data, "pos"), &object->pos)
			|| !calc_angle(object, json_obj_get(data, "angle")))
		return (0);
	if ((tmp = json_obj_get(data, "color")))
	{
		if (!color_from_json(tmp, &object->color))
			return (0);
	}
	else
		vec3cl_fill(&object->color, 1, 1, 1);
	if (!(tmp = json_obj_get(data, "type")) || tmp->str.type != JSON_STRING
			|| !obj_props(object, tmp->str.value, data, &object->type))
		return (0);
	if (object->type == OBJ_MESH && !parse_mesh(scene, object, data))
		return (0);
	if ((tmp = json_obj_get(data, "material")) && tmp->obj.type == JSON_OBJECT)
	{
		if (!parse_material(object, &tmp->obj))
			return (0);
	}
	else
		obj_default_material(object);
	return (1);
}
