/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 16:38:16 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/12 19:55:06 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

char	*ft_strrchr(const char *s, int ch)
{
	char	c;
	size_t	i;
	size_t	len;
	char	*res;

	c = (char)ch;
	i = 0;
	len = ft_strlen(s);
	res = (char *)NULL;
	while (i <= len)
		if (s[i++] == c)
			res = (char *)(s + i - 1);
	return (res);
}
