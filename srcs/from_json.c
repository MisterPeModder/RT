/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_json.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 17:44:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/31 13:10:13 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"
#include <libft_base/stringft.h>

int					float_from_json(const t_json_value *val, float *f)
{
	if (!val)
		return (0);
	else if (val->n_i.type == JSON_INT)
	{
		*f = (float)val->n_i.value;
		return (1);
	}
	else if (val->n_d.type == JSON_DOUBLE)
	{
		*f = val->n_d.value;
		return (1);
	}
	else
		return (0);
}

int					bool_from_json(const t_json_value *val, t_bool *f)
{
	if (!val)
		return (0);
	else if (val->bol.type == JSON_BOOL)
	{
		*f = (int)val->bol.value == 1 ? true : false;
		return (1);
	}
	else
		return (0);
}

int					vec3f_from_json(const t_json_value *arr, t_vec3f *vec)
{
	if (!arr || arr->arr.type != JSON_ARRAY || arr->arr.values_num != 3 ||
			!float_from_json(json_arr_get(&arr->arr, 0), &vec->x) ||
			!float_from_json(json_arr_get(&arr->arr, 1), &vec->y) ||
			!float_from_json(json_arr_get(&arr->arr, 2), &vec->z))
		return (0);
	return (1);
}

int					angle_from_json(const t_json_value *arr, t_vec3f *vec)
{
	if (!vec3f_from_json(arr, vec))
		return (0);
	vec->x = to_radians(vec->x);
	vec->y = to_radians(vec->y);
	vec->z = to_radians(vec->z);
	return (1);
}

int					color_from_json(const t_json_value *arr, t_vec3f *color)
{
	t_json_value	*tmp;

	if (!arr || arr->arr.type != JSON_ARRAY || arr->arr.values_num != 3)
		return (0);
	if (!(tmp = json_arr_get(&arr->arr, 0)) || tmp->n_i.type != JSON_INT ||
			tmp->n_i.value < 0 || tmp->n_i.value > 255)
		return (0);
	color->x = tmp->n_i.value / 255.f;
	if (!(tmp = json_arr_get(&arr->arr, 1)) || tmp->n_i.type != JSON_INT ||
			tmp->n_i.value < 0 || tmp->n_i.value > 255)
		return (0);
	color->y = tmp->n_i.value / 255.f;
	if (!(tmp = json_arr_get(&arr->arr, 2)) || tmp->n_i.type != JSON_INT ||
			tmp->n_i.value < 0 || tmp->n_i.value > 255)
		return (0);
	color->z = tmp->n_i.value / 255.f;
	return (1);
}
