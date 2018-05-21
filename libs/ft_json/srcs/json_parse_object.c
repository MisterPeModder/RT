/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse_object.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 06:09:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 11:23:56 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/list.h>
#include <stddef.h>
#include "json.h"
#include "json_internal.h"

static t_json_value		*json_parse_obj_init(t_json_value *v,
		t_json_str_it *it, t_json_parse_res *res, int *has_parent)
{
	t_json_value		*obj;

	if (!json_lexing(v, it, res, 1))
		return (NULL);
	if (!(obj = json_make_value(JSON_OBJECT)))
		return (NULL);
	if (*has_parent && json_is_special(v, '}'))
		*has_parent = 2;
	return (obj);
}

static t_json_value		*json_parse_obj_middle(t_json_value *v,
		t_json_str_it *it, t_json_parse_res *res, t_json_value *obj)
{
	if (!json_is_special(v, '}') && (!json_parse_obj_value(it, obj, v, res)
				|| !json_lexing(v, it, res, 0)) &&
			json_release(&obj) && json_rd(v))
		return (NULL);
	return (v);
}

static t_json_value		*json_parse_obj_finish(t_json_value *v,
		t_json_value *obj, t_json_parse_res *res, t_json_str_it *it)
{
	if (!json_is_special(v, ','))
	{
		if (json_is_special(v, '}') ||
				!(json_release(&obj) && json_rd(v) && (--res->line + 1)))
			return (obj);
		return (json_ret_error(res, "missing comma ','"));
	}
	if (!json_lexing(v, it, res, 0) && json_rd(v) && json_release(&obj))
		return (NULL);
	return ((t_json_value *)~(ptrdiff_t)NULL);
}

static t_json_value		*json_parse_obj_end(t_json_parse_res *res,
		t_json_value *obj, t_json_value *v)
{
	json_release(&obj);
	json_rd(v);
	return (json_ret_error(res, "cannot have comma ',' on last element"));
}

t_json_value			*json_parse_object(t_json_str_it *it, int has_parent,
		t_json_parse_res *res)
{
	t_json_value		*obj;
	t_json_value		v;
	int					is_begin;
	t_json_value		*ret;

	if (!(obj = json_parse_obj_init(&v, it, res, &has_parent)))
		return (NULL);
	if ((is_begin = 1) && has_parent == 2)
		return (obj);
	while (!json_is_special(&v, '}'))
	{
		if (is_begin && !has_parent && json_is_special(&v, '{') && json_rd(&v))
		{
			if (!json_lexing(&v, it, res, (is_begin = 0)) && json_release(&obj))
				return (NULL);
		}
		else if (is_begin && !has_parent && json_release(&obj))
			return (json_ret_error(res, "main object must start with '{'"));
		if (!json_parse_obj_middle(&v, it, res, obj) ||
				(ret = json_parse_obj_finish(&v, obj, res, it)) == NULL)
			return (NULL);
		if (ret != ((t_json_value *)~(ptrdiff_t)NULL))
			return (ret);
	}
	return (json_parse_obj_end(res, obj, &v));
}
