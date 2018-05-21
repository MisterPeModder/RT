/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_lex_string.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 13:36:07 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/04 23:03:10 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/list.h>
#include <libft_base/stringft.h>
#include <libft_containers/dyn_str.h>
#include "json.h"
#include "json_internal.h"

static int				json_lex_str_setback(t_json_parse_res *res, int lc)
{
	res->col = lc;
	--res->line;
	return (1);
}

static int				json_special_char(t_dynstr *dyn, t_json_parse_res *res,
		char c)
{
	if (c == '"' || c == '\\' || c == '/')
		dynstr_pushc(dyn, c);
	else if (c == 'b')
		dynstr_pushc(dyn, '\b');
	else if (c == 'f')
		dynstr_pushc(dyn, '\f');
	else if (c == 'n')
		dynstr_pushc(dyn, '\n');
	else if (c == 'r')
		dynstr_pushc(dyn, '\r');
	else if (c == 't')
		dynstr_pushc(dyn, '\t');
	else if (c == 'u')
	{
		dynstr_deinit(dyn);
		return (json_ret_errorv(res,
					"Unicode escape sequences aren't supported yet."));
	}
	else
	{
		dynstr_deinit(dyn);
		return (json_ret_errorv(res, "invalid escape sequence"));
	}
	return (1);
}

static void				json_str_init_logic(t_json_value *v, t_dynstr *dyn,
		int *special)
{
	json_init_value(v, JSON_STRING);
	dynstr_init(dyn, 32);
	*special = 0;
}

static int				json_str_logic(t_dynstr *dyn, int *special, char c,
		t_json_value *v)
{
	if (c == '\\')
	{
		*special = 1;
		return (3);
	}
	else if (c == '"')
	{
		v->str.value = dyn->str;
		return (0);
	}
	else if (c == '\n')
		return (1);
	return (2);
}

int						json_lex_str(t_json_value *v, t_json_str_it *it,
		t_json_parse_res *res, int lc)
{
	t_dynstr			dyn;
	char				c;
	int					special;
	int					ret;

	json_str_init_logic(v, &dyn, &special);
	while (!it->str.end && (lc = res->col) * 0 + 1)
	{
		c = json_it_next(it, res);
		if (special)
		{
			if (!json_special_char(&dyn, res, c) && json_rd(v))
				return (0);
			special = 0;
		}
		else if (!(ret = json_str_logic(&dyn, &special, c, v)))
			return (1);
		else if (ret == 1 && json_lex_str_setback(res, lc))
			break ;
		else if (ret == 2)
			dynstr_pushc(&dyn, c);
	}
	json_rd(v);
	dynstr_deinit(&dyn);
	return (json_ret_errorv(res, "unclosed string"));
}
