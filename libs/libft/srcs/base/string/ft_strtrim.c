/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 21:15:27 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/13 18:01:33 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

static size_t	get_str_len(char **s)
{
	size_t	i;
	size_t	last_ch;

	while (**s && (**s == ' ' || **s == '\n' || **s == '\t'))
		++(*s);
	if (!**s)
		return ((size_t)0);
	i = 0;
	last_ch = 0;
	while ((*s)[i])
	{
		if (!((*s)[i] == ' ' || (*s)[i] == '\n' || (*s)[i] == '\t'))
			last_ch = i;
		++i;
	}
	return (last_ch + 1);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	len;
	char	*res;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char *)s;
	len = get_str_len(&str);
	if (!(res = ft_strnew(len)))
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = str[i];
		++i;
	}
	return (res);
}
