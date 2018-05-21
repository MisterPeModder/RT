/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_make_value.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 01:32:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 06:30:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json_internal.h"

t_json_value			*json_make_value(t_json_vtype type)
{
	t_json_value		*v;

	if (!(v = (t_json_value *)malloc(sizeof(t_json_value))))
		return (NULL);
	v->obj.type = type;
	if (type == JSON_OBJECT && !(v->obj.data = hm_make(0, 0)))
	{
		free(v);
		return (NULL);
	}
	else if (type == JSON_STRING)
		v->str.value = NULL;
	else if (type == JSON_ARRAY)
	{
		v->arr.values = NULL;
		v->arr.values_num = 0;
	}
	return (v);
}

void					json_init_value(t_json_value *v, t_json_vtype type)
{
	v->obj.type = type;
	if (type == JSON_OBJECT)
		v->obj.data = NULL;
	else if (type == JSON_STRING)
		v->str.value = NULL;
	else if (type == JSON_ARRAY)
	{
		v->arr.values = NULL;
		v->arr.values_num = 0;
	}
}
