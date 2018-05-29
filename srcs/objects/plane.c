/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 06:50:22 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 14:27:30 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "rt.h"

float				plane_intersect(t_object *obj, t_vec3f *origin, t_vec3f *u)
{
	float			l_dot_n;
	t_vec3f			tmp;

	if (vec3f_dot_product(u, &obj->facing) > 0)
		vec3f_neg(&obj->facing, &obj->facing);
	if (fabs(l_dot_n = vec3f_dot_product(u, &obj->facing)) < 1e-6)
		return (FLT_MAX);
	return (vec3f_dot_product(vec3f_sub(&obj->pos, origin, &tmp),
				&obj->facing) / l_dot_n);
}

void				plane_normal(t_object *o, t_rt_result *r)
{
	r->normal = o->facing;
}

int					plane_init(t_object *object, const t_json_object *data)
{
	object->release = NULL;
	object->intersect = &plane_intersect;
	object->normal = &plane_normal;
	(void)data;
	return (1);
}
