/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_release.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 13:46:00 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/17 06:04:24 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_containers/hashmap.h"

static void				hm_release_val(void **value)
{
	if (*value)
		free(*value);
	*value = NULL;
}

void					hm_release_node(t_hmnode *n, void (*d)(void *))
{
	hm_release_val((void **)&n->key);
	(*d)(n->value);
	hm_release_val((void **)&n);
}

void					hm_release(t_hashmap **map, void (*d)(void *))
{
	size_t			i;
	t_hmnode		*n;
	t_hmnode		*tmp;

	if (!map || !*map)
		return ;
	if (!d)
		d = &free;
	i = 0;
	while (i < (*map)->length)
	{
		n = (*map)->buckets[i];
		while (n)
		{
			tmp = n->next;
			hm_release_node(n, d);
			n = tmp;
		}
		(*map)->buckets[i] = NULL;
		++i;
	}
	hm_release_val((void **)&(*map)->buckets);
	free(*map);
	*map = NULL;
}
