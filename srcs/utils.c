/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:52:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/07 00:33:44 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

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

int					vec3f_from_json(const t_json_value *arr, t_vec3f *vec)
{
	if (!arr || arr->arr.type != JSON_ARRAY || arr->arr.values_num != 3 ||
			!float_from_json(json_arr_get(&arr->arr, 0), &vec->x) ||
			!float_from_json(json_arr_get(&arr->arr, 1), &vec->y) ||
			!float_from_json(json_arr_get(&arr->arr, 2), &vec->z))
		return (0);
	return (1);
}

void				*ret_free(void *obj)
{
	if (obj)
		free(obj);
	return (NULL);
}
