/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 00:41:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 01:02:53 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"

t_vec2f			*vec2i_normalize(const t_vec2i *src, t_vec2f *dst)
{
	float		norm;

	norm = vec2i_norm(src);
	dst->x = (float)src->x / norm;
	dst->y = (float)src->y / norm;
	return (dst);
}

t_vec2f			*vec2f_normalize(const t_vec2f *src, t_vec2f *dst)
{
	float		norm;

	norm = vec2f_norm(src);
	dst->x = src->x / norm;
	dst->y = src->y / norm;
	return (dst);
}

t_vec2d			*vec2d_normalize(const t_vec2d *src, t_vec2d *dst)
{
	double		norm;

	norm = vec2d_norm(src);
	dst->x = src->x / norm;
	dst->y = src->y / norm;
	return (dst);
}
