/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:43:50 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/15 11:17:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lneedle;
	char	*hs;
	char	*ne;

	hs = (char *)haystack;
	ne = (char *)needle;
	j = 0;
	lneedle = ft_strlen(needle);
	while (hs[j] && j < len)
	{
		i = 0;
		while (j + i < len && ne[i] && *(hs + j + i) == ne[i])
			++i;
		if (j + i <= len && i == lneedle)
			return (hs + j);
		++j;
	}
	if (!*hs && !*ne)
		return (hs);
	return (NULL);
}
