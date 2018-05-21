/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 21:54:43 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/27 21:56:37 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"

t_vec2i			*vec2i_sub(const t_vec2i *l, const t_vec2i *r, t_vec2i *d)
{
	d->x = l->x - r->x;
	d->y = l->y - r->y;
	return (d);
}

t_vec2f			*vec2f_sub(const t_vec2f *l, const t_vec2f *r, t_vec2f *d)
{
	d->x = l->x - r->x;
	d->y = l->y - r->y;
	return (d);
}

t_vec2d			*vec2d_sub(const t_vec2d *l, const t_vec2d *r, t_vec2d *d)
{
	d->x = l->x - r->x;
	d->y = l->y - r->y;
	return (d);
}
