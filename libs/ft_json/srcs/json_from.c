/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_from.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 01:26:18 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 15:05:59 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/character.h>
#include "json.h"
#include "json_internal.h"

static t_json_parse_res	*json_check_after_main(t_json_parse_res *res,
		t_json_str_it *it, int f)
{
	char c;

	if (!(f & JFLAG_IGNORE_EXTRA))
		return (res);
	while (!it->str.end)
	{
		c = json_it_peek(it);
		if (it->str.is_file && it->file.i >= it->file.data_size)
			break ;
		if (!ft_isspace(json_it_next(it, res)) && json_release(&res->obj))
		{
			json_set_error(res, "Non-whitespace characters are not allowed"
					" after main object");
			return (res);
		}
	}
	return (res);
}

t_json_parse_res		*json_from_file(int fd, int f)
{
	t_json_str_it		it;
	t_json_parse_res	*res;
	t_json_value		*obj;

	if (!(res = (t_json_parse_res *)malloc(sizeof(t_json_parse_res))))
		return (NULL);
	json_init_iterator(&it, 1, NULL, fd);
	res->err = NULL;
	res->line = 1;
	res->col = 0;
	res->obj = NULL;
	res->flags = f;
	obj = json_parse_object(&it, 0, res);
	if (obj)
		res->obj = obj;
	return (json_check_after_main(res, &it, f));
}

t_json_parse_res		*json_from_str(const char *src, int f)
{
	t_json_str_it		it;
	t_json_parse_res	*res;
	t_json_value		*obj;

	if (!(res = (t_json_parse_res *)malloc(sizeof(t_json_parse_res))))
		return (NULL);
	json_init_iterator(&it, 0, src, 0);
	res->err = NULL;
	res->line = 1;
	res->col = 0;
	res->obj = NULL;
	res->flags = f;
	obj = json_parse_object(&it, 0, res);
	if (obj)
		res->obj = obj;
	return (json_check_after_main(res, &it, f));
}
