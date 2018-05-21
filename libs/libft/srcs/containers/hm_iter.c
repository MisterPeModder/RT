/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_iter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 17:54:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/17 18:42:41 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_containers/hashmap.h"

void					hm_iter_init(t_hashmap *map, t_hmiterator *it)
{
	it->map = map;
	it->i = 0;
	it->curr = map->buckets[0];
}

int						hm_iter_next(t_hmiterator *it)
{
	if (it->map == NULL || it->i >= it->map->length)
		return (0);
	while (it->i < it->map->length - 1)
	{
		if (!it->curr)
			it->curr = it->map->buckets[++it->i];
		while (it->curr)
		{
			if (it->curr->value)
			{
				it->value = it->curr->value;
				it->key = it->curr->key;
				it->curr = it->curr->next;
				return (1);
			}
			it->curr = it->curr->next;
		}
	}
	return (0);
}
