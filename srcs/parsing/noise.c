/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   noise.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 07:35:06 by jloro             #+#    #+#             */
/*   Updated: 2018/08/23 09:02:11 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <libft_base/stringft.h>

static int			parse_type_noise(t_json_value *tmp, t_type_noise *type)
{
	if (ft_strcmp(tmp->str.value, "wood") == 0 && (*type = WOOD))
		return (1);
	else if (ft_strcmp(tmp->str.value, "water") == 0 && (*type = WATER))
		return (1);
	else if (ft_strcmp(tmp->str.value, "perlin") == 0 && (*type = PERLIN))
		return (1);
	else if (ft_strcmp(tmp->str.value, "sin_marble") == 0 &&
			(*type = SIN_MARBLE))
		return (1);
	else if (ft_strcmp(tmp->str.value, "line_marble") == 0 &&
			(*type = LINE_MARBLE))
		return (1);
	return (0);
}

static int			parse_noise3(const t_json_object *data, t_noise *noise)
{
	t_json_value	*tmp;

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

static int			parse_noise2(const t_json_object *data, t_noise *noise)
{
	t_json_value	*tmp;

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
	return (1);
}

int					parse_noise(const t_json_object *data, t_noise *noise)
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
		noise->octave = 10;
	if (!parse_noise2(data, noise) || !parse_noise3(data, noise))
		return (0);
	return (1);
}
