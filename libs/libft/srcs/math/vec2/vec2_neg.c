/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_neg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 20:11:00 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/27 20:13:40 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"

t_vec2i			*vec2i_neg(const t_vec2i *src, t_vec2i *dst)
{
	dst->x = -src->x;
	dst->y = -src->y;
	return (dst);
}

t_vec2f			*vec2f_neg(const t_vec2f *src, t_vec2f *dst)
{
	dst->x = -src->x;
	dst->y = -src->y;
	return (dst);
}

t_vec2d			*vec2d_neg(const t_vec2d *src, t_vec2d *dst)
{
	dst->x = -src->x;
	dst->y = -src->y;
	return (dst);
}
