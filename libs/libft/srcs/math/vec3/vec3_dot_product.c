/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_dot_product.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 03:15:35 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/01 14:25:34 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec3.h"

float			vec3i_dot_product(const t_vec3i *r, const t_vec3i *l)
{
	return (r->x * l->x + r->y * l->y + l->z * r->z);
}

float			vec3f_dot_product(const t_vec3f *r, const t_vec3f *l)
{
	return (r->x * l->x + r->y * l->y + l->z * r->z);
}

double			vec3d_dot_product(const t_vec3d *r, const t_vec3d *l)
{
	return (r->x * l->x + r->y * l->y + l->z * r->z);
}
