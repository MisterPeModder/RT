/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strconcat.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/16 15:48:45 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/16 15:52:30 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_base/base.h"

char	*ft_strconcat(char *s1, char *s2, int free_args)
{
	char	*res;
	size_t	ls1;

	if ((!s1 && s2) || (!s2 && s1))
	{
		res = ft_strdup(!s1 ? s2 : s1);
	}
	else
	{
		ls1 = s1 ? ft_strlen(s1) : (size_t)0;
		if ((!s1 && !s2) || !(res = ft_strnew(ls1 + ft_strlen(s2))))
			return (NULL);
		ft_strcpy(res, s1);
		ft_strcpy(res + ls1, s2);
	}
	if (free_args == 1 || free_args == 3)
		free(s1);
	if (free_args == 2 || free_args == 3)
		free(s2);
	return (res);
}
