/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_put.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:43:43 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/03 08:25:38 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

int						json_obj_put(t_json_object *obj, t_json_value *v,
		const char *k)
{
	t_json_value		*tmp;

	if (!obj || obj->type != JSON_OBJECT || !k || !v)
		return (0);
	if ((tmp = hm_get(obj->data, k)))
		json_release(&tmp);
	hm_put(obj->data, k, v);
	return (1);
}

int						json_arr_put(t_json_array *arr, t_json_value *v,
		size_t i)
{
	if (!arr || arr->type != JSON_ARRAY || !v || i >= arr->values_num)
		return (0);
	if (arr->values[i])
		json_release(arr->values + i);
	arr->values[i] = v;
	return (1);
}
