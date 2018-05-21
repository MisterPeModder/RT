/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_make.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 16:36:14 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/17 05:15:45 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_containers/hashmap.h"

t_hashmap				*hm_make(size_t power, float load_factor)
{
	t_hashmap		*map;
	size_t			i;

	if (!(map = (t_hashmap *)malloc(sizeof(t_hashmap))))
		return (NULL);
	if (power == 0 || power >= sizeof(size_t) * 8)
		power = HM_DEFAULT_POWER;
	map->length = 1ul << power;
	if (!(map->buckets = (t_hmnode **)malloc(sizeof(void *) * map->length)))
	{
		free(map);
		return (NULL);
	}
	i = 0;
	while (i < map->length)
		map->buckets[i++] = NULL;
	map->load_factor = load_factor ? load_factor : HM_DEFAULT_LOAD_FACTOR;
	map->size = 0;
	return (map);
}
