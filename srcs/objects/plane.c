/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 06:50:22 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 16:17:04 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

t_hitlst			*plane_intersect(t_object *o, t_vec3f *cam, t_vec3f *u)
{
	float			l_dot_n;
	float			d;
	t_vec3f			tmp[2];

	if ((l_dot_n = vec3f_dot_product(u, &o->props.plane.normal)) == 0)
		return (NULL);
	d = vec3f_dot_product(vec3f_sub(&o->pos, cam, &tmp[0]),
			&o->props.plane.normal) / l_dot_n;
	return (hitlstnew(o, d, vec3f_add(&o->pos,
					vec3f_mul(u, d, &tmp[1]), &tmp[0]),
				&o->props.plane.normal));
}

int					plane_init(t_object *object, const t_json_object *data)
{
	t_vec3f			*v;

	object->release = NULL;
	object->intersect = &plane_intersect;
	v = &object->props.plane.normal;
	vec3f_fill(v, 0, 1, 0);
	rotate_x(v, v, object->angle.x);
	rotate_y(v, v, object->angle.y);
	rotate_z(v, v, object->angle.z);
	(void)data;
	return (1);
}
