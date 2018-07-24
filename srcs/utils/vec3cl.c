/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3cl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 01:36:02 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/24 03:53:28 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

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

t_clfloat3			*vec3cl_cross(t_clfloat3 *v1, t_clfloat3 *v2,
		t_clfloat3 *dst)
{
	dst->x = v1->y * v2->z - v1->z * v2->y;
	dst->y = v1->z * v2->x - v1->x * v2->z;
	dst->z = v1->x * v2->y - v1->y * v2->x;
	return (dst);
}

t_clfloat3			*vec3cl_mul(t_clfloat3 *v, float a, t_clfloat3 *dst)
{
	dst->x = v->x * a;
	dst->y = v->y * a;
	dst->z = v->z * a;
	return (dst);
}
