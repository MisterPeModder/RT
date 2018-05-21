/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 03:27:24 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 03:27:34 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec3.h"

t_vec3i			*vec3i_sub(const t_vec3i *l, const t_vec3i *r, t_vec3i *d)
{
	d->x = l->x - r->x;
	d->y = l->y - r->y;
	d->z = l->z - r->z;
	return (d);
}

t_vec3f			*vec3f_sub(const t_vec3f *l, const t_vec3f *r, t_vec3f *d)
{
	d->x = l->x - r->x;
	d->y = l->y - r->y;
	d->z = l->z - r->z;
	return (d);
}

t_vec3d			*vec3d_sub(const t_vec3d *l, const t_vec3d *r, t_vec3d *d)
{
	d->x = l->x - r->x;
	d->y = l->y - r->y;
	d->z = l->z - r->z;
	return (d);
}
