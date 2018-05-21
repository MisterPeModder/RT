/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/04 23:06:14 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 05:40:12 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/calc.h"

double					ft_pow(double nb, int power)
{
	int					p;
	double				value;

	value = nb;
	p = power < 0 ? -power : power;
	if (p > 0)
		while (p-- > 1)
			value *= nb;
	else
		value = power ? 0 : 1;
	return (power < 0 ? 1 / value : value);
}
