/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_mul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 21:57:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/27 22:16:11 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"

t_vec2i			*vec2i_mul(const t_vec2i *l, int r, t_vec2i *d)
{
	d->x = l->x * r;
	d->y = l->y * r;
	return (d);
}

t_vec2f			*vec2f_mul(const t_vec2f *l, float r, t_vec2f *d)
{
	d->x = l->x * r;
	d->y = l->y * r;
	return (d);
}

t_vec2d			*vec2d_mul(const t_vec2d *l, double r, t_vec2d *d)
{
	d->x = l->x * r;
	d->y = l->y * r;
	return (d);
}
