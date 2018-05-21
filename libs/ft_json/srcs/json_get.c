/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/23 16:13:11 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/23 16:40:01 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"

t_json_value			*json_obj_get(const t_json_object *obj, const char *k)
{
	return (!obj || obj->type != JSON_OBJECT || !k ?
			NULL : hm_get(obj->data, k));
}

t_json_value			*json_arr_get(const t_json_array *arr, size_t i)
{
	return (!arr || arr->type != JSON_ARRAY || i >= arr->values_num ?
			NULL : arr->values[i]);
}
