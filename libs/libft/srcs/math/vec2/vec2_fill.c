/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:47:58 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/27 19:50:40 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"

t_vec2i			*vec2i_fill(t_vec2i *dst, int x, int y)
{
	dst->x = x;
	dst->y = y;
	return (dst);
}

t_vec2f			*vec2f_fill(t_vec2f *dst, float x, float y)
{
	dst->x = x;
	dst->y = y;
	return (dst);
}

t_vec2d			*vec2d_fill(t_vec2d *dst, double x, double y)
{
	dst->x = x;
	dst->y = y;
	return (dst);
}
