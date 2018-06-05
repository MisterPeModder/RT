/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3cl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 01:36:02 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 01:45:47 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_clfloat3			*vec3cl_fill(t_clfloat3 *vec,
		t_clfloat x, t_clfloat y, t_clfloat z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
	return (vec);
}

t_clfloat3			*vec3cl_add(t_clfloat3 *rhs, t_clfloat3 *lhs,
		t_clfloat3 *dst)
{
	dst->x = rhs->x + lhs->x;
	dst->y = rhs->y + lhs->y;
	dst->z = rhs->z + lhs->z;
	return (dst);
}
