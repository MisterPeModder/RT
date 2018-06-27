/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3cl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 01:36:02 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/26 21:48:47 by jloro            ###   ########.fr       */
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

t_clfloat3			*vec3cl_sub(t_clfloat3 *v1, t_clfloat3 *v2, t_clfloat3 *d)
{
	d->x = v1->x - v2->x;
	d->y = v1->y - v2->y;
	d->z = v1->z - v2->z;
	return (d);
}

t_clfloat3			*vec3cl_neg(t_clfloat3 *v, t_clfloat3 *d)
{
	d->x = -v->x;
	d->y = -v->y;
	d->z = -v->z;
	return (d);
}

t_clfloat3			*vec3cl_normalize(t_clfloat3 *v, t_clfloat3 *d)
{
	float			norm;

	norm = sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
	d->x = v->x / norm;
	d->y = v->y / norm;
	d->z = v->z / norm;
	return (d);
}

float			vec3cl_dot_product(const t_clfloat3 *r, const t_clfloat3 *l)
{
	return (r->x * l->x + r->y * l->y + l->z * r->z);
}
