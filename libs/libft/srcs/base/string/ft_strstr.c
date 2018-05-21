/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/10 17:06:57 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/15 09:49:25 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	lneedle;
	char	*hs;
	char	*ne;

	hs = (char *)haystack;
	ne = (char *)needle;
	i = 0;
	lneedle = ft_strlen(needle);
	while (*hs)
	{
		i = 0;
		while (ne[i] && *(hs + i) == ne[i])
			++i;
		if (i == lneedle)
			return (hs);
		++hs;
	}
	if (!*hs && !*ne)
		return (hs);
	return (NULL);
}
