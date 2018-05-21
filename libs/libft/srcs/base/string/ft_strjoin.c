/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 21:02:38 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/22 12:27:11 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	ls1;

	if ((!s1 && s2) || (!s2 && s1))
		return ((char *)(!s1 ? s2 : s1));
	ls1 = s1 ? ft_strlen(s1) : (size_t)0;
	if ((!s1 && !s2) || !(res = ft_strnew(ls1 + ft_strlen(s2))))
		return (NULL);
	ft_strcpy(res, s1);
	ft_strcpy(res + ls1, s2);
	return (res);
}
