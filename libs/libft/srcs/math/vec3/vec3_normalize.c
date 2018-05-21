/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_normalize.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 03:20:38 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 03:20:48 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec3.h"

t_vec3f			*vec3i_normalize(const t_vec3i *src, t_vec3f *dst)
{
	float		norm;

	norm = vec3i_norm(src);
	dst->x = (float)src->x / norm;
	dst->y = (float)src->y / norm;
	dst->z = (float)src->z / norm;
	return (dst);
}

t_vec3f			*vec3f_normalize(const t_vec3f *src, t_vec3f *dst)
{
	float		norm;

	norm = vec3f_norm(src);
	dst->x = src->x / norm;
	dst->y = src->y / norm;
	dst->z = src->z / norm;
	return (dst);
}

t_vec3d			*vec3d_normalize(const t_vec3d *src, t_vec3d *dst)
{
	double		norm;

	norm = vec3d_norm(src);
	dst->x = src->x / norm;
	dst->y = src->y / norm;
	dst->z = src->z / norm;
	return (dst);
}
