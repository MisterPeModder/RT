/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 16:54:23 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/04 23:39:26 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/list.h>
#include <libft_base/memory.h>
#include <libft_base/stringft.h>
#include "json.h"
#include "json_internal.h"

static size_t			json_count_ln(const t_json_value *val)
{
	size_t				i;
	t_hmiterator		it;
	size_t				c;

	c = 1;
	if (val->obj.type == JSON_OBJECT)
	{
		hm_iter_init(val->obj.data, &it);
		while (hm_iter_next(&it))
			c += json_count_ln(it.value);
		++c;
	}
	else if (val->obj.type == JSON_ARRAY)
	{
		i = 0;
		while (i < val->arr.values_num)
			c += json_count_ln(val->arr.values[i++]);
		++c;
	}
	return (c);
}

char					**json_to_tab(const t_json_value *val)
{
	char				**tab;

	if (!(tab = ft_memalloc(sizeof(char *) * (json_count_ln(val) + 1))))
		return (NULL);
	if (!json_val_to_tab(val, tab))
		ft_strtabdel(&tab);
	return (tab);
}

char					*json_to_str(const t_json_value *val)
{
	char				**tab;
	size_t				i;
	size_t				len;
	char				*ret;

	if (!(tab = json_to_tab(val)))
		return (NULL);
	i = 0;
	len = 0;
	while (tab[i])
		len += ft_strlen(tab[i++]) + 1;
	if (!(ret = ft_strnew(len)))
	{
		ft_strtabdel(&tab);
		return (NULL);
	}
	i = 0;
	while (tab[i])
	{
		ft_strcat(ret, tab[i++]);
		ft_strcat(ret, "\n");
	}
	ft_strtabdel(&tab);
	return (ret);
}
