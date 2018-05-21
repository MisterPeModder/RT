/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 03:16:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 03:17:51 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec3.h"

t_vec3i			*vec3i_fill(t_vec3i *dst, int x, int y, int z)
{
	dst->x = x;
	dst->y = y;
	dst->z = z;
	return (dst);
}

t_vec3f			*vec3f_fill(t_vec3f *dst, float x, float y, float z)
{
	dst->x = x;
	dst->y = y;
	dst->z = z;
	return (dst);
}

t_vec3d			*vec3d_fill(t_vec3d *dst, double x, double y, double z)
{
	dst->x = x;
	dst->y = y;
	dst->z = z;
	return (dst);
}
