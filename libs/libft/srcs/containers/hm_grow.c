/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_grow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 04:52:44 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 18:46:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_containers/hashmap.h"

static t_hmnode			**hm_make_new_buckets(t_hashmap *map)
{
	t_hmnode			**nbuckets;
	size_t				nsize;
	size_t				i;

	nsize = map->length << 1;
	if (!(nbuckets = (t_hmnode **)malloc(sizeof(t_hmnode *) * nsize)))
		return (NULL);
	i = 0;
	while (i < nsize)
		nbuckets[i++] = NULL;
	return (nbuckets);
}

static void				hm_reassign(t_hmnode **nb, size_t nlen, t_hmnode *curr)
{
	t_hmnode			*tmp;
	size_t				pos;

	while (curr)
	{
		tmp = curr->next;
		pos = hm_hash(curr->key) & nlen;
		if (nb[pos])
			curr->next = nb[pos];
		else
			curr->next = NULL;
		nb[pos] = curr;
		curr = tmp;
	}
}

void					hm_grow(t_hashmap *map)
{
	t_hmnode			**nbuckets;
	size_t				i;
	size_t				nlen;

	if (!(nbuckets = hm_make_new_buckets(map)))
		return ;
	i = 0;
	nlen = (map->length << 1) - 1;
	while (i < map->length)
		hm_reassign(nbuckets, nlen, map->buckets[i++]);
	free(map->buckets);
	map->buckets = nbuckets;
	map->length <<= 1;
}
