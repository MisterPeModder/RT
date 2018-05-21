/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 23:03:54 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 01:02:32 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"
#include "libft_math/calc.h"

float			vec2i_norm(const t_vec2i *vec)
{
	return (ft_fsqrt(vec->x * vec->x + vec->y * vec->y));
}

float			vec2f_norm(const t_vec2f *vec)
{
	return (ft_fsqrt(vec->x * vec->x + vec->y * vec->y));
}

double			vec2d_norm(const t_vec2d *vec)
{
	return (ft_sqrt(vec->x * vec->x + vec->y * vec->y));
}
