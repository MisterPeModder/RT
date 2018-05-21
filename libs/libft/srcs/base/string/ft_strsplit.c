/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 10:36:22 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/13 17:59:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

static size_t	count_words(char *s, char c)
{
	int		in_word;
	size_t	i;

	in_word = 0;
	i = 0;
	while (*s)
	{
		if (!in_word && *s != c)
		{
			in_word = 1;
			++i;
		}
		else if (*s == c)
			in_word = 0;
		++s;
	}
	return (i);
}

static char		*get_word(char **s, char c)
{
	size_t	l;
	char	*res;
	size_t	i;

	l = 0;
	while ((*s)[l] && (*s)[l] != c)
		++l;
	if (!(res = ft_strnew(l)))
		return (NULL);
	i = 0;
	while (**s && **s != c)
	{
		res[i] = **s;
		++i;
		++(*s);
	}
	return (res);
}

char			**ft_strsplit(char const *s, char c)
{
	char	**tab;
	size_t	l;
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	l = count_words((char *)s, c);
	if (!s || !(tab = ft_memalloc(sizeof(char *) * (l + 1))))
		return (NULL);
	i = 0;
	str = (char *)s;
	while (i < l)
	{
		while (*str == c)
			++str;
		tab[i] = get_word(&str, c);
		++i;
	}
	tab[i] = 0;
	return (tab);
}
