/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:50:25 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 18:04:13 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

void	*ft_memchr(const void *s, int ch, size_t n)
{
	unsigned char	*str;
	unsigned char	c;
	size_t			i;

	str = (unsigned char *)s;
	c = (unsigned char)ch;
	i = 0;
	while (i < n)
		if (str[i++] == c)
			return ((void *)((int *)s + i - 1));
	return (NULL);
}
