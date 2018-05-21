/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:20:15 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/14 17:07:00 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	size_t	dlen;
	size_t	i;

	dlen = ft_strlen(dest);
	i = 0;
	while (i < n && src[i])
	{
		dest[dlen + i] = src[i];
		++i;
	}
	dest[dlen + i] = 0;
	return (dest);
}
