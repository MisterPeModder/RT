/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_div.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 03:14:41 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 03:15:02 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec3.h"

t_vec3i			*vec3i_div(const t_vec3i *l, int r, t_vec3i *d)
{
	d->x = l->x / r;
	d->y = l->y / r;
	d->z = l->z / r;
	return (d);
}

t_vec3f			*vec3f_div(const t_vec3f *l, float r, t_vec3f *d)
{
	d->x = l->x / r;
	d->y = l->y / r;
	d->z = l->z / r;
	return (d);
}

t_vec3d			*vec3d_div(const t_vec3d *l, double r, t_vec3d *d)
{
	d->x = l->x / r;
	d->y = l->y / r;
	d->z = l->z / r;
	return (d);
}
