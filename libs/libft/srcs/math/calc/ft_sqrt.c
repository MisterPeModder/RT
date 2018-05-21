/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 22:32:40 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/01 14:24:09 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/calc.h"

float			ft_fsqrt(float num)
{
	float		res;
	float		tmp;

	res = 1;
	tmp = (res * res) / num - 1.f;
	while ((tmp < 0 ? -tmp : tmp) >= 0.000001)
	{
		res = ((num / res) + res) / 2;
		tmp = (res * res) / num - 1.f;
	}
	return (res);
}

double			ft_sqrt(double num)
{
	double		res;
	double		tmp;

	res = 1;
	tmp = (res * res) / num - 1.0;
	while ((tmp < 0 ? -tmp : tmp) >= 0.00000001)
	{
		res = ((num / res) + res) / 2;
		tmp = (res * res) / num - 1.0;
	}
	return (res);
}
