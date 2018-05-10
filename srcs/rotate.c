/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 07:32:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 09:10:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "rtv1.h"

t_vec3f				*rotate_x(const t_vec3f *src, t_vec3f *dst, float rx)
{
	float			cos_x;
	float			sin_x;

	cos_x = cos(rx);
	sin_x = sin(rx);
	return (vec3f_fill(dst,
				src->x,
				cos_x * src->y + sin_x * src->z,
				cos_x * src->z + sin_x * src->y));
}

t_vec3f				*rotate_y(const t_vec3f *src, t_vec3f *dst, float ry)
{
	float			cos_y;
	float			sin_y;

	cos_y = cos(ry);
	sin_y = sin(ry);
	return (vec3f_fill(dst,
				cos_y * src->x - sin_y * src->z,
				src->y,
				cos_y * src->z + sin_y * src->x));
}

t_vec3f				*rotate_z(const t_vec3f *src, t_vec3f *dst, float rz)
{
	float			cos_z;
	float			sin_z;

	cos_z = cos(rz);
	sin_z = sin(rz);
	return (vec3f_fill(dst,
				cos_z * src->x - sin_z * src->y,
				cos_z * src->y - sin_z * src->x,
				sin_z * src->x + src->z));
}
