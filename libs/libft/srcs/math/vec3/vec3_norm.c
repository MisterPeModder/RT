/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_norm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 03:21:09 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 03:21:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec3.h"
#include "libft_math/calc.h"

float			vec3i_norm(const t_vec3i *vec)
{
	return (ft_fsqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}

float			vec3f_norm(const t_vec3f *vec)
{
	return (ft_fsqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}

double			vec3d_norm(const t_vec3d *vec)
{
	return (ft_fsqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z));
}
