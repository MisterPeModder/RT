/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 10:18:05 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/12 19:48:15 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"
#include <stdlib.h>

void	*ft_memmove(void *d, const void *s, size_t n)
{
	unsigned char	*dst;
	unsigned char	*src;

	if (d == s || n == 0)
		return (d);
	dst = (unsigned char *)d;
	src = (unsigned char *)s;
	if (src < dst)
		while (n--)
			dst[n] = src[n];
	else
		ft_memcpy(d, s, n);
	return (d);
}
