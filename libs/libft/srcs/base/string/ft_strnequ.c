/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 20:14:21 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/17 21:44:08 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	if (!s1)
		return (!s2 ? 1 : 0);
	else if (!s2)
		return (!s1 ? 1 : 0);
	return (ft_strncmp(s1, s2, n) == 0 ? 1 : 0);
}
