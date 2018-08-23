/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 21:46:57 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/23 04:22:04 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include <libft_base/io.h>
#include "rt.h"

static t_mat_props	mat_props(char *str)
{
	if (ft_strequ(str, "reflective"))
		return (MAT_REFLECTIVE);
	else if (ft_strequ(str, "refractive"))
		return (MAT_REFRACTIVE);
	else if (ft_strequ(str, "portal"))
		return (MAT_PORTAL);
	else if (ft_strequ(str, "negative"))
		return (MAT_NEGATIVE);
	else
		return (MAT_NONE);
}

static int			parse_type_noise(t_json_value *tmp, t_type_noise *type)
{
	if (ft_strcmp(tmp->str.value, "wood") == 0 && (*type = WOOD))
		return (1);
	else if (ft_strcmp(tmp->str.value, "water") == 0 && (*type = WATER))
		return (1);
	else if (ft_strcmp(tmp->str.value, "perlin") == 0 && (*type = PERLIN))
		return (1);
	else if (ft_strcmp(tmp->str.value, "sin_marble") == 0 && (*type = SIN_MARBLE))
		return (1);
	else if (ft_strcmp(tmp->str.value, "line_marble") == 0 && (*type = LINE_MARBLE))
		return (1);
	else
		return (0);;
}

/*
** Activate it while noise will be ready. Same for lines in parse_material.
*/

static int		parse_noise(const t_json_object *data, t_noise *noise)
{
	t_json_value	*tmp;

	noise->perturb = 0;
	if ((tmp = json_obj_get(data, "persistence")))
	{
		if (!float_from_json(tmp, &noise->pers))
			return (0);
	}
	else
		noise->pers = -1;
	if ((tmp = json_obj_get(data, "octave")))
	{
		if (!int_from_json(tmp, &noise->octave) || noise->octave <= 0)
			return (0);
	}
	else
		noise->octave = -1;
	if ((tmp = json_obj_get(data, "seed")))
	{
		if (!int_from_json(tmp, &noise->seed) || noise->seed <= 0)
			return (0);
	}
	else
		noise->seed = 1000;
	if ((tmp = json_obj_get(data, "amplitude")))
	{
		if (!float_from_json(tmp, &noise->amp) || noise->amp <= 0)
			return (0);
	}
	else
		noise->amp = -1;
	if ((tmp = json_obj_get(data, "type")))
	{
			if (tmp->obj.type != JSON_STRING
				|| !parse_type_noise(tmp, &noise->type))
				return (0);
	}
	else
		noise->type = NONE;
	if ((tmp = json_obj_get(data, "color")))
	{
		if (tmp && tmp->bol.type == JSON_BOOL && tmp->bol.value == 1)
			noise->perturb |= COLOR;
	}
	if ((tmp = json_obj_get(data, "normal")))
	{
		if (tmp && tmp->bol.type == JSON_BOOL && tmp->bol.value == 1)
			noise->perturb |= NORMAL;
	}
	return (1);
}

static int			obj_parse_portal(t_object *obj, const t_json_object *data)
{
	if (!vec3f_from_json(json_obj_get(data, "output_pos"), &obj->mat.p_out))
	{
		ft_putendl_fd("Invalid portal output position", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int					parse_material(t_object *object, const t_json_object *data)
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
	if (object->mat.props == MAT_PORTAL && !obj_parse_portal(object, data))
		return (0);
	object->mat.has_shadow = 1;
	if ((tmp = json_obj_get(data, "has_shadow")))
	{
		if (tmp->bol.type != JSON_BOOL)
		{
			ft_putendl_fd("\"has_shadow\" should be a boolean", STDERR_FILENO);
			return (0);
		}
		object->mat.has_shadow = tmp->bol.value;
	}
	if ((tmp = json_obj_get(data, "perturbation")))
	{
		if (tmp->obj.type != JSON_OBJECT || !parse_noise(&tmp->obj, &object->mat.noise))
			return (0);
		object->mat.has_noise = 1;
	}
	else
		object->mat.has_noise = 0;
	return (1);
}
