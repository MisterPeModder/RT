/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 14:15:57 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/13 10:18:49 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*s;

	if (!(s = ft_strnew(ft_strlen(src))))
		return (NULL);
	ft_strcpy(s, src);
	return (s);
}
