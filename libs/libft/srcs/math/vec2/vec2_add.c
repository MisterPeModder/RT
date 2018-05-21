/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 21:51:37 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/01 14:24:51 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"

t_vec2i			*vec2i_add(const t_vec2i *l, const t_vec2i *r, t_vec2i *d)
{
	d->x = l->x + r->x;
	d->y = l->y + r->y;
	return (d);
}

t_vec2f			*vec2f_add(const t_vec2f *l, const t_vec2f *r, t_vec2f *d)
{
	d->x = l->x + r->x;
	d->y = l->y + r->y;
	return (d);
}

t_vec2d			*vec2d_add(const t_vec2d *l, const t_vec2d *r, t_vec2d *d)
{
	d->x = l->x + r->x;
	d->y = l->y + r->y;
	return (d);
}
