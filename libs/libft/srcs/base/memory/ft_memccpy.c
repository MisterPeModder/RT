/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 10:10:24 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/15 12:33:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	const char	*s;
	char		*d;
	size_t		i;

	s = (const char *)src;
	d = (char *)dest;
	i = n;
	while (i-- > 0)
		if ((*d++ = *s++) == (char)c)
			return (d);
	return (NULL);
}
