/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/11 12:49:29 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/15 12:12:05 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

int			ft_atoi(const char *str)
{
	int		i;
	int		sign;
	int		num;

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
