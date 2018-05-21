/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashmap_internal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/15 12:34:43 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/19 11:32:48 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHMAP_INTERNAL_H
# define HASHMAP_INTERNAL_H

# include <stdlib.h>

# define HM_DEFAULT_POWER 4
# define HM_DEFAULT_LOAD_FACTOR .75f

typedef struct			s_hmnode
{
	char				*key;
	void				*value;
	struct s_hmnode		*next;
}						t_hmnode;

typedef struct			s_hashmap
{
	t_hmnode			**buckets;
	size_t				length;
	float				load_factor;
	size_t				size;
}						t_hashmap;

typedef struct			s_hmiterator
{
	t_hashmap			*map;
	size_t				i;
	t_hmnode			*curr;
	char				*key;
	void				*value;
}						t_hmiterator;

/*
** djb2 hash algorithm
*/
unsigned long			hm_hash(const char *str);

void					hm_release_node(t_hmnode *n, void (*d)(void *));

size_t					hm_bucket_size(t_hmnode *node);

void					hm_grow(t_hashmap *map);

#endif
