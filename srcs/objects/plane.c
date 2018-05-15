/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 06:50:22 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/15 18:26:06 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "rtv1.h"

float				plane_intersect(t_object *obj, t_vec3f *origin, t_vec3f *u)
{
	float			l_dot_n;
	t_vec3f			tmp;

	if (fabs(l_dot_n = vec3f_dot_product(u, &obj->props.plane.normal)) < 1e-6)
		return (FLT_MAX);
	return (vec3f_dot_product(vec3f_sub(&obj->pos, origin, &tmp),
				&obj->props.plane.normal) / l_dot_n);
}

void				plane_normal(t_object *o, t_rt_result *r)
{
	r->normal = o->props.plane.normal;
}

int					plane_behind(t_object *object, const t_vec3f *p)
{
	t_vec3f			po;

	return (vec3f_dot_product(&object->props.plane.normal,
				vec3f_sub(&object->pos, p, &po)) > 0);
}

int					plane_init(t_object *object, const t_json_object *data)
{
	object->release = NULL;
	object->intersect = &plane_intersect;
	object->normal = &plane_normal;
	object->inside = plane_behind;
	vec3f_fill(&object->props.plane.normal, 0, 1, 0);
	rotate_x(&object->props.plane.normal, object->angle.x);
	rotate_y(&object->props.plane.normal, object->angle.y);
	rotate_z(&object->props.plane.normal, object->angle.z);
	(void)data;
	return (1);
}
