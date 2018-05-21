/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_put.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 17:53:11 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 18:46:26 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/stringft.h"
#include "libft_base/memory.h"
#include "libft_containers/hashmap.h"

static t_hmnode			*hm_make_node(const char *key, void *value)
{
	t_hmnode		*node;

	if (!(node = (t_hmnode *)malloc(sizeof(t_hmnode))))
		return (NULL);
	if (key)
		node->key = ft_strdup(key);
	else
		node->key = NULL;
	node->value = value;
	node->next = NULL;
	return (node);
}

static int				hm_try_update(t_hashmap *map, const char *key,
		void *value, size_t i)
{
	t_hmnode		*curr;

	curr = map->buckets[i];
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			free(curr->value);
			curr->value = value;
			return (1);
		}
		curr = curr->next;
	}
	return (0);
}

void					hm_put(t_hashmap *map, const char *key, void *value)
{
	size_t			i;
	t_hmnode		*curr;
	t_hmnode		*tmp;

	if (map->size + 1 >= (size_t)(map->length * map->load_factor))
		hm_grow(map);
	if (!value)
		return ;
	i = hm_hash(key) & (map->length - 1);
	if (!map->buckets[i])
		map->buckets[i] = hm_make_node(key, value);
	else
	{
		if (hm_try_update(map, key, value, i) ||
				!(curr = hm_make_node(key, value)))
			return ;
		tmp = map->buckets[i];
		map->buckets[i] = curr;
		curr->next = tmp;
	}
	++map->size;
}

void					hm_put_cpy(t_hashmap *map, const char *key,
		const void *val, size_t len)
{
	void				*mem;

	if (len == 0 || !(mem = malloc(len)))
		return ;
	ft_memcpy(mem, val, len);
	hm_put(map, key, mem);
}
