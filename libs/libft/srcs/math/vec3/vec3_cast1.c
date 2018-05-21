/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_cast1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 03:10:30 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 03:10:56 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec3.h"

t_vec3f			*vec3_itof(const t_vec3i *src, t_vec3f *dst)
{
	dst->x = (float)src->x;
	dst->y = (float)src->y;
	dst->z = (float)src->z;
	return (dst);
}

t_vec3d			*vec3_itod(const t_vec3i *src, t_vec3d *dst)
{
	dst->x = (double)src->x;
	dst->y = (double)src->y;
	dst->z = (double)src->z;
	return (dst);
}

t_vec3i			*vec3_ftoi(const t_vec3f *src, t_vec3i *dst)
{
	dst->x = (int)src->x;
	dst->y = (int)src->y;
	dst->z = (int)src->z;
	return (dst);
}
