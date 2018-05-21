/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_val_to_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 16:19:07 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 06:38:40 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include "json.h"
#include "json_internal.h"

static int				json_obj_to_tab_helper(char **sub, char ***tab,
		const char *it_key)
{
	size_t				j;

	j = 0;
	while (sub[j])
	{
		++*tab;
		if (!j)
			**tab = ft_strconcat("\t", ft_strconcat(json_stringify(it_key),
						ft_strconcat(": ", *sub, 0), 3), 2);
		else
			**tab = ft_strconcat("\t", sub[j], 0);
		++j;
		if (!**tab)
		{
			ft_strtabdel(&sub);
			return (0);
		}
	}
	return (1);
}

static int				json_obj_to_tab(const t_json_value *val, char **tab)
{
	t_hmiterator		it;
	char				**sub;
	int					first;

	if (!(*tab = ft_strdup("{")))
		return (0);
	hm_iter_init(val->obj.data, &it);
	first = 1;
	while (hm_iter_next(&it))
	{
		if (!(sub = json_to_tab(it.value)))
			return (0);
		if (!first)
			*tab = ft_strconcat(*tab, ",", 1);
		first = 0;
		if (!json_obj_to_tab_helper(sub, &tab, it.key))
			return (0);
		ft_strtabdel(&sub);
	}
	if (!(*(tab + (*tab ? 1 : 0)) = ft_strdup("}")))
		return (0);
	return (1);
}

static int				json_arr_to_tab_helper(char **sub, char ***tab)
{
	size_t				j;

	j = 0;
	while (sub[j])
	{
		++*tab;
		**tab = ft_strconcat("\t", sub[j], 0);
		++j;
		if (!**tab)
		{
			ft_strtabdel(&sub);
			return (0);
		}
	}
	return (1);
}

static int				json_arr_to_tab(const t_json_value *val, char **tab)
{
	size_t				i;
	char				**sub;
	int					first;

	if (!(*tab = ft_strdup("[")))
		return (0);
	i = 0;
	first = 1;
	while (i < val->arr.values_num)
	{
		if (!(sub = json_to_tab(val->arr.values[i])))
			return (0);
		if (!first)
			*tab = ft_strconcat(*tab, ",", 1);
		first = 0;
		if (!json_arr_to_tab_helper(sub, &tab))
			return (0);
		ft_strtabdel(&sub);
		++i;
	}
	if (!(*(tab + (*tab ? 1 : 0)) = ft_strdup("]")))
		return (0);
	return (1);
}

int						json_val_to_tab(const t_json_value *val, char **tab)
{
	if (val->obj.type == JSON_OBJECT)
		return (json_obj_to_tab(val, tab));
	else if (val->obj.type == JSON_ARRAY)
		return (json_arr_to_tab(val, tab));
	else if (val->obj.type == JSON_STRING)
		*tab = json_stringify(val->str.value);
	else if (val->obj.type == JSON_INT)
		*tab = ft_itoa(val->n_i.value);
	else if (val->obj.type == JSON_DOUBLE)
		*tab = json_suppress_zeros(ft_dtoa(val->n_d.value, JSON_FP_PRECISION));
	else if (val->obj.type == JSON_BOOL)
		*tab = ft_strdup(val->bol.value ? "true" : "false");
	else if (val->obj.type == JSON_NULL)
		*tab = ft_strdup("null");
	else
		return (0);
	return (1);
}
