/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:01:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/25 13:38:44 by jhache           ###   ########.fr       */
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
	else if (ft_strequ(str, "cube") && (*type = OBJ_CUBE))
		return (cube_init(object, data));
	else if (ft_strequ(str, "pyramid") && (*type = OBJ_PYRAMID))
		return (pyramid_init(object, data));
	else if (ft_strequ(str, "paraboloid") && (*type = OBJ_PARABOLOID))
		return (paraboloid_init(object, data));
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
	vec3cl_fill(&object->dir, 0, 0, -1);
	rotate_x(&object->dir, angle.x);
	rotate_y(&object->dir, angle.y);
	rotate_z(&object->dir, angle.z);
	vec3cl_fill(&object->right, 1, 0, 0);
	rotate_x(&object->right, angle.x);
	rotate_y(&object->right, angle.y);
	rotate_z(&object->right, angle.z);
	return (1);
}

static t_mat_props	mat_props(char *str)
{
	if (ft_strequ(str, "reflective"))
		return (MAT_REFLECTIVE);
	else if (ft_strequ(str, "refractive"))
		return (MAT_REFLECTIVE);
	else if (ft_strequ(str, "portal"))
		return (MAT_PORTAL);
	else if (ft_strequ(str, "negative"))
		return (MAT_NEGATIVE);
	else
		return (MAT_NONE);
}

/*
** Activate it while noise will be ready. Same for lines in parse_material.
*/
/*static t_noise		*parse_noise(const t_json_value *data, t_noise *noise)
{
	t_json_value	*tmp;

	if ((tmp = json_arr_get(&data->arr, 0)) && tmp->n_i.value == 1)
		noise->has_noise = tmp->n_i.value;
	else
	{
		noise->has_noise = 0;
		return (noise);
	}
	if ((tmp = json_arr_get(&data->arr, 1)) && tmp->n_d.value > 0)
		noise->freq = tmp->n_d.value;
	if ((tmp = json_arr_get(&data->arr, 2)) && tmp->n_i.value > 0)
		noise->depth = tmp->n_i.value;
	if ((tmp = json_arr_get(&data->arr, 3))
		&& ft_strcmp(tmp->str.value, "wood") == 0
		&& ft_strcmp(tmp->str.value, "sin_marble") == 0
		&& ft_strcmp(tmp->str.value, "line_marble") == 0)
		noise->type = tmp->str.value;
	return (noise);
}*/

static int			parse_material(t_object *object, const t_json_object *data)
{
	t_json_value	*tmp;

	if ((tmp = json_obj_get(data, "property")) && tmp->obj.type == JSON_STRING)
		object->mat.props = mat_props(tmp->str.value);
	else
		object->mat.props = MAT_NONE;
	if (!(float_from_json(json_obj_get(data, "coefficient"),
					&object->mat.props_coef)))
		object->mat.props_coef = 0.f;
	if (object->mat.props_coef < 0.f || object->mat.props_coef > 1.f)
		object->mat.props_coef = ((object->mat.props_coef < 0.f) ? 0.f : 1.f);
	if (!(float_from_json(json_obj_get(data, "refractive_index"),
					&object->mat.refractive_index)))
		object->mat.refractive_index = 1.f;
	/*if ((tmp = json_obj_get(data, "noise")) && tmp->obj.type == JSON_ARRAY)
		object->mat.noise = parse_noise(tmp, object->mat.noise);
	else
		object->mat.noise->has_noise = 0;*/
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
		vec3cl_fill(&object->color, 1, 1, 1);
	if (!(tmp = json_obj_get(data, "type")) || tmp->str.type != JSON_STRING ||
			!obj_props(object, tmp->str.value, data, &object->type))
		return (0);
	if ((tmp = json_obj_get(data, "material"))
		&& tmp->obj.type == JSON_OBJECT)
		parse_material(object, &tmp->obj);
	else
	{
		object->mat.props = MAT_NONE;
		object->mat.props_coef = 0.f;
		object->mat.refractive_index = 1.f;
	}
	return (1);
}
