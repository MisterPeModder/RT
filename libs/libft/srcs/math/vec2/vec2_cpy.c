/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_cpy.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 19:52:29 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/27 19:55:38 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"

t_vec2i			*vec2i_cpy(const t_vec2i *src, t_vec2i *dst)
{
	dst->x = src->x;
	dst->y = src->y;
	return (dst);
}

t_vec2f			*vec2f_cpy(const t_vec2f *src, t_vec2f *dst)
{
	dst->x = src->x;
	dst->y = src->y;
	return (dst);
}

t_vec2d			*vec2d_cpy(const t_vec2d *src, t_vec2d *dst)
{
	dst->x = src->x;
	dst->y = src->y;
	return (dst);
}
