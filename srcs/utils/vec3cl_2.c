/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3cl_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 03:53:44 by jhache            #+#    #+#             */
/*   Updated: 2018/07/24 03:54:49 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <math.h>

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

float				vec3cl_dot_product(const t_clfloat3 *r, const t_clfloat3 *l)
{
	return (r->x * l->x + r->y * l->y + l->z * r->z);
}
