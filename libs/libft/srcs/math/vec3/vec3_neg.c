/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_neg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 03:19:44 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 03:19:55 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec3.h"

t_vec3i			*vec3i_neg(const t_vec3i *src, t_vec3i *dst)
{
	dst->x = -src->x;
	dst->y = -src->y;
	dst->z = -src->z;
	return (dst);
}

t_vec3f			*vec3f_neg(const t_vec3f *src, t_vec3f *dst)
{
	dst->x = -src->x;
	dst->y = -src->y;
	dst->z = -src->z;
	return (dst);
}

t_vec3d			*vec3d_neg(const t_vec3d *src, t_vec3d *dst)
{
	dst->x = -src->x;
	dst->y = -src->y;
	dst->z = -src->z;
	return (dst);
}
