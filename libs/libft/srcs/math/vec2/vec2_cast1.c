/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_cast1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:58:05 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/27 20:02:38 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"

t_vec2f			*vec2_itof(const t_vec2i *src, t_vec2f *dst)
{
	dst->x = (float)src->x;
	dst->y = (float)src->y;
	return (dst);
}

t_vec2d			*vec2_itod(const t_vec2i *src, t_vec2d *dst)
{
	dst->x = (double)src->x;
	dst->y = (double)src->y;
	return (dst);
}

t_vec2i			*vec2_ftoi(const t_vec2f *src, t_vec2i *dst)
{
	dst->x = (int)src->x;
	dst->y = (int)src->y;
	return (dst);
}
