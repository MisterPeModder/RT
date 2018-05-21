/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_parse_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 06:55:35 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/07 00:29:54 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/list.h>
#include <stddef.h>
#include "json.h"
#include "json_internal.h"

static int				json_parse_arr_value(t_json_str_it *it,
		t_list **lst, t_json_value *first, t_json_parse_res *res)
{
	t_list				*nlst;
	t_json_value		*v;

	if (!(nlst = ft_lstnew(NULL, 0)))
		return (0);
	if (!(v = json_parse_value(it, first, res)))
	{
		ft_lstdelone(&nlst, NULL);
		return (0);
	}
	nlst->content = v;
	ft_lstadd(lst, nlst);
	return (1);
}

static t_json_value		*json_convert_lst2arr(t_list *elems)
{
	t_json_value		*arr;
	t_list				*n;
	size_t				i;

	if (!(arr = json_make_value(JSON_ARRAY)))
	{
		ft_lstdel(&elems, &json_rel4lst);
		return (NULL);
	}
	arr->arr.values_num = ft_lstlen(elems);
	if (!(arr->arr.values = malloc(sizeof(t_json_value) * arr->arr.values_num)))
	{
		json_release(&arr);
		ft_lstdel(&elems, &json_rel4lst);
		return (NULL);
	}
	n = elems;
	i = arr->arr.values_num - 1;
	while (n)
	{
		arr->arr.values[i--] = n->content;
		n = n->next;
	}
	ft_lstdel(&elems, NULL);
	return (arr);
}

static t_json_value		*json_parse_array_helper(t_json_str_it *it,
		t_json_parse_res *res, t_list **elems, t_json_value *v)
{
	if (!json_is_special(v, ']') && (!json_parse_arr_value(it, elems,
					v, res) || !json_lexing(v, it, res, 0)) &&
			json_rd(v))
	{
		ft_lstdel(elems, &json_rel4lst);
		return (NULL);
	}
	if (!json_is_special(v, ','))
	{
		if (json_is_special(v, ']'))
			return (json_convert_lst2arr(*elems));
		ft_lstdel(elems, &json_rel4lst);
		--res->line;
		json_rd(v);
		return (json_ret_error(res, "missing comma ','"));
	}
	if (!json_lexing(v, it, res, 0) && json_rd(v))
	{
		ft_lstdel(elems, &json_rel4lst);
		return (NULL);
	}
	return ((t_json_value *)~((ptrdiff_t)NULL));
}

t_json_value			*json_parse_array(t_json_str_it *it,
		t_json_parse_res *res)
{
	t_json_value		v;
	t_list				*elems;
	t_json_value		*ret;

	if (!json_lexing(&v, it, res, 1))
		return (NULL);
	if (json_is_special(&v, ']'))
		return (json_make_value(JSON_ARRAY));
	elems = NULL;
	while (!json_is_special(&v, ']'))
	{
		if ((ret = json_parse_array_helper(it, res, &elems, &v)) == NULL)
			return (NULL);
		if (ret != ((t_json_value *)~((ptrdiff_t)NULL)))
			return (ret);
	}
	ft_lstdel(&elems, &json_rel4lst);
	return (json_ret_error(res, "cannot have comma ',' on last element"));
}
