/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 14:37:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 06:20:59 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/memory.h"
#include "libft_base/stringft.h"
#include "libft_containers/dyn_str.h"

void				dynstr_push(t_dynstr *str, const char *c)
{
	size_t			len;
	char			*tmp;
	size_t			nlen;

	if (!str)
		return ;
	if ((len = ft_strlen(c)) + str->length > str->capacity)
	{
		nlen = str->capacity + str->increment;
		while (nlen < len + str->length)
			nlen += str->increment;
		if (!(tmp = ft_strnew(nlen)))
			return ;
		if (str->str)
		{
			ft_memcpy(tmp, str->str, str->capacity);
			free(str->str);
		}
		str->str = tmp;
		str->capacity = nlen;
	}
	if (!str->str && !(str->str = ft_strnew(str->capacity)))
		return ;
	str->length += len;
	ft_strcat(str->str, c);
}

void				dynstr_pushc(t_dynstr *str, char c)
{
	char			tmp[2];

	tmp[0] = c;
	tmp[1] = 0;
	dynstr_push(str, tmp);
}
