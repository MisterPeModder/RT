/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_stringify.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 15:55:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/04 16:58:47 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include "json_internal.h"

static int				json_sfy_should_escape(char c)
{
	return (c == '"' || c == '\\' || c == '/' || c == '\b' || c == '\f'
			|| c == '\n' || c == '\r' || c == '\t');
}

static size_t			json_sfy_len(const char *src)
{
	size_t				len;

	len = 0;
	while (*src)
	{
		if (json_sfy_should_escape(*src))
			++len;
		++len;
		++src;
	}
	return (len);
}

static void				json_sfy_fill(const char *src, char *str)
{
	size_t				i;

	i = 1;
	while (*src)
	{
		if (json_sfy_should_escape(*src))
			str[i++] = '\\';
		if (*src == '\b')
			str[i++] = 'b';
		else if (*src == '\f')
			str[i++] = 'f';
		else if (*src == '\n')
			str[i++] = 'n';
		else if (*src == '\r')
			str[i++] = 'r';
		else if (*src == '\t')
			str[i++] = 't';
		else
			str[i++] = *src;
		++src;
	}
}

char					*json_stringify(const char *src)
{
	char				*str;

	if (!src || !(str = ft_strnew(json_sfy_len(src) + 2)))
		return (NULL);
	*str = '"';
	json_sfy_fill(src, str);
	ft_strcat(str, "\"");
	return (str);
}
