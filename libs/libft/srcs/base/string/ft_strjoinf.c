/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:29:34 by yguaye            #+#    #+#             */
/*   Updated: 2017/12/21 14:32:53 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

char			*ft_strjoinf(char **s1, char **s2)
{
	char		*res;

	res = ft_strjoin(*s1, *s2);
	ft_strdel(s1);
	ft_strdel(s2);
	return (res);
}

char			*ft_strjoinf1(char **s1, const char *s2)
{
	char		*res;

	res = ft_strjoin(*s1, s2);
	ft_strdel(s1);
	return (res);
}

char			*ft_strjoinf2(const char *s1, char **s2)
{
	char		*res;

	res = ft_strjoin(s1, *s2);
	ft_strdel(s2);
	return (res);
}
