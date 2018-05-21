/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 17:15:05 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/14 17:05:54 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	dlen;

	i = 0;
	dlen = ft_strlen(dest);
	while (src[i])
	{
		dest[dlen + i] = src[i];
		++i;
	}
	dest[dlen + i] = 0;
	return (dest);
}
