/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:50:23 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/12 19:52:26 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	char		*d;
	char		*s;
	size_t		n;
	size_t		dlen;

	d = dst;
	s = (char *)src;
	n = siz;
	while (n-- && *d)
		d++;
	dlen = (size_t)(d - dst);
	n = siz - dlen;
	if (n == 0)
		return (dlen + ft_strlen(s));
	while (*s)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = 0;
	return (dlen + (size_t)(s - src));
}
