/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parsing_helpers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 07:00:22 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 07:56:57 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include "json.h"
#include "json_internal.h"

int						json_is_special(t_json_value *val, char c)
{
	return (val->obj.type == JSON_SPECIAL_CHAR && val->bol.value == c);
}

t_json_value			*json_parse_value(t_json_str_it *it, t_json_value *val,
		t_json_parse_res *res)
{
	t_json_value		*ret;

	if (json_is_special(val, '{'))
		return (json_parse_object(it, 1, res));
	else if (json_is_special(val, '['))
		return (json_parse_array(it, res));
	if (!(ret = ft_memdup(val, sizeof(t_json_value))))
		return (NULL);
	ft_bzero(val, sizeof(t_json_value));
	val->obj.type = JSON_NULL;
	return (ret);
}
