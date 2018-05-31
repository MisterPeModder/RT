/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:58:06 by jhache            #+#    #+#             */
/*   Updated: 2018/05/31 13:59:17 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float3		*rotate_x(float3 *vec, float rx)
{
	float			cos_x;
	float			sin_x;
	float3			tmp;

	tmp = *vec;
	cos_x = cos(rx);
	sin_x = sin(rx);
	tmp.y = cos_x * tmp.y - sin_x * tmp.z;
	tmp.z = cos_x * (*vec).z + sin_x * (*vec).y;
	*vec = tmp;
	return (vec);
}

static float3		*rotate_y(float3 *vec, float ry)
{
	float			cos_y;
	float			sin_y;
	float3			tmp;

	tmp = *vec;
	cos_y = cos(ry);
	sin_y = sin(ry);
	tmp.x = cos_y * tmp.x + sin_y * tmp.z;
	tmp.z = cos_y * (*vec).z - sin_y * (*vec).x;
	*vec = tmp;
	return (vec);
}

static float3		*rotate_z(float3 *vec, float rz)
{
	float			cos_z;
	float			sin_z;
	float3			tmp;

	tmp = *vec;
	cos_z = cos(rz);
	sin_z = sin(rz);
	tmp.x = cos_z * tmp.x - sin_z * tmp.y;
	tmp.y = cos_z * (*vec).y + sin_z * (*vec).x;
	*vec = tmp;
	return (vec);
}
