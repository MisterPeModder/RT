/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse_obj_value.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 11:23:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 11:24:13 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "json.h"
#include "json_internal.h"

int						json_parse_obj_value(t_json_str_it *it,
		t_json_value *obj, t_json_value *first, t_json_parse_res *res)
{
	t_json_value		second;
	t_json_value		*v;

	if (first->obj.type != JSON_STRING)
		return (json_ret_errorv(res, "non-string keys are not allowed!"));
	if (!json_lexing(&second, it, res, 1))
		return (0);
	if (!json_is_special(&second, ':') && json_rd(&second))
		return (json_ret_errorv(res, "must have colon ':' after key"));
	if (!json_lexing(&second, it, res, 0))
		return (0);
	if (!(v = json_parse_value(it, &second, res)) && json_rd(&second))
		return (0);
	if (v->obj.type == JSON_SPECIAL_CHAR && json_release(&v))
		return (json_ret_errorv(res, "unexpected value"));
	if (hm_get(obj->obj.data, first->str.value) && json_release(&v))
		return (json_ret_errorv(res, "cannot use the same key twice!"));
	hm_put(obj->obj.data, first->str.value, v);
	return (1);
}
