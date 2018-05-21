/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 00:16:10 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 00:17:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

long			ft_atol(const char *str)
{
	int			i;
	long		sign;
	long		num;

	i = 0;
	while (str[i] && ft_isspace((int)str[i]))
		++i;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		sign = str[i] == '-' ? -1 : 1;
		++i;
	}
	num = 0;
	while (ft_isdigit((int)str[i]))
	{
		num *= 10;
		num += str[i] - '0';
		++i;
	}
	return (sign * num);
}
