/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 13:20:19 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/12 14:00:53 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"
#include <stdlib.h>

void	*ft_memalloc(size_t size)
{
	unsigned char	*tab;
	size_t			i;

	if (!(tab = (unsigned char *)malloc(size)))
		return (NULL);
	i = 0;
	while (i < size)
		tab[i++] = (unsigned char)0;
	return ((void *)tab);
}
