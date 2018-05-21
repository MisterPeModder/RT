/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_collisions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 19:43:39 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/15 09:59:12 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_containers/hashmap.h"

size_t					hm_collisions(t_hashmap *map)
{
	size_t				i;
	size_t				len;
	size_t				tmp;

	i = 0;
	len = 0;
	while (i < map->length)
	{
		len += (tmp = hm_bucket_size(map->buckets[i])) > 1 ? tmp : 0;
		++i;
	}
	return (len);
}
