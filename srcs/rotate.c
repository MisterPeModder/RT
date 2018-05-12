/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 07:32:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/12 11:50:20 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

t_vec3f				*rotate_x(t_vec3f *vec, float rx)
{
	float			cos_x;
	float			sin_x;

	cos_x = cos(rx);
	sin_x = sin(rx);
	return (vec3f_fill(vec,
				vec->x,
				cos_x * vec->y - sin_x * vec->z,
				cos_x * vec->z + sin_x * vec->y));
}

t_vec3f				*rotate_y(t_vec3f *vec, float ry)
{
	float			cos_y;
	float			sin_y;

	cos_y = cos(ry);
	sin_y = sin(ry);
	return (vec3f_fill(vec,
				cos_y * vec->x + sin_y * vec->z,
				vec->y,
				cos_y * vec->z - sin_y * vec->x));
}

t_vec3f				*rotate_z(t_vec3f *vec, float rz)
{
	float			cos_z;
	float			sin_z;

	cos_z = cos(rz);
	sin_z = sin(rz);
	return (vec3f_fill(vec,
				cos_z * vec->x - sin_z * vec->y,
				cos_z * vec->y - sin_z * vec->x,
				vec->z));
}
