/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 11:51:46 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/12 19:51:29 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

char	*ft_strchr(const char *s, int ch)
{
	char	c;
	size_t	i;
	size_t	len;

	c = (char)ch;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
		if (s[i++] == c)
			return ((char *)(s + i - 1));
	return (NULL);
}
