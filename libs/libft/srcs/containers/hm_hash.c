/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hm_hash.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 16:35:11 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/19 11:36:01 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_containers/hashmap.h"

unsigned long			hm_hash(const char *str)
{
	unsigned long	hash;
	unsigned int	c;

	if (!str)
		return (0);
	hash = 5381;
	while ((c = (unsigned int)*str++))
		hash = ((hash << 5) + hash) + c;
	return (hash);
}
