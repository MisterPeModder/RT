/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 06:50:22 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/17 13:52:51 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "rtv1.h"

float				plane_intersect(t_object *obj, t_vec3f *origin, t_vec3f *u)
{
	float			l_dot_n;
	t_vec3f			tmp;

	if (fabs(l_dot_n = vec3f_dot_product(u, &obj->facing)) < 1e-6)
		return (FLT_MAX);
	return (vec3f_dot_product(vec3f_sub(&obj->pos, origin, &tmp),
				&obj->facing) / l_dot_n);
}

void				plane_normal(t_object *o, t_rt_result *r)
{
	r->normal = o->facing;
}
