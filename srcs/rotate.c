/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 07:32:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 01:32:33 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

cl_float3				*rotate_x(cl_float3 *vec, t_clfloat rx)
{
	t_clfloat			cos_x;
	t_clfloat			sin_x;

	cos_x = cos(rx);
	sin_x = sin(rx);
	return (vec3cl_fill(vec,
				vec->x,
				cos_x * vec->y - sin_x * vec->z,
				cos_x * vec->z + sin_x * vec->y));
}

cl_float3				*rotate_y(cl_float3 *vec, t_clfloat ry)
{
	t_clfloat			cos_y;
	t_clfloat			sin_y;

	cos_y = cos(ry);
	sin_y = sin(ry);
	return (vec3cl_fill(vec,
				cos_y * vec->x + sin_y * vec->z,
				vec->y,
				cos_y * vec->z - sin_y * vec->x));
}

cl_float3				*rotate_z(cl_float3 *vec, t_clfloat rz)
{
	t_clfloat			cos_z;
	t_clfloat			sin_z;

	cos_z = cos(rz);
	sin_z = sin(rz);
	return (vec3cl_fill(vec,
				cos_z * vec->x - sin_z * vec->y,
				cos_z * vec->y + sin_z * vec->x,
				vec->z));
}
