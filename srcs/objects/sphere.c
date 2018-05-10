/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 23:16:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 18:30:05 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

#include <stdio.h>

//CONVERTED
t_hitlst			*sphere_intersect(t_object *o, t_vec3f *cam, t_vec3f *u)
{
	float			i[3];
	float			delta;
	t_hitlst		*lst;
	t_vec3f			v[2];
	float			d;

	i[0] = u->x * u->x + u->y * u->y + u->z * u->z;
	i[1] = 2 * (u->x * (cam->x - o->pos.x)
			+ u->y * (cam->y - o->pos.y)
			+ u->z * (cam->z - o->pos.z));
	i[2] = ((cam->x - o->pos.x) * (cam->x - o->pos.x)
			+ (cam->y - o->pos.y) * (cam->y - o->pos.y)
			+ (cam->z - o->pos.z) * (cam->z - o->pos.z))
		- o->props.sphere.radius * o->props.sphere.radius;
	delta = i[1] * i[1] - 4 * i[0] * i[2];
	if (delta < 0)
		return (NULL);
	else if (delta == 0)
		lst = hitlstnew(o, -i[1], vec3f_mul(u, -i[0], v),
				vec3f_sub(v, cam, &v[1]));
	else
	{
		i[2] = (float)sqrt(delta);
		d = (-i[1] + i[2]) / (2 * i[0]);
		lst = hitlstnew(o, d, vec3f_mul(u, d, v), vec3f_sub(v, cam, &v[1]));
		if (lst)
		{
			d = (-i[1] - i[2]) / (2 * i[0]);
			lst->next = hitlstnew(o, d, vec3f_mul(u, d, v),
					vec3f_sub(v, cam, &v[1]));
		}
	}
	return (lst);
}

int					sphere_init(t_object *object, const t_json_object *data)
{
	object->release = NULL;
	object->intersect = &sphere_intersect;
	return (float_from_json(json_obj_get(data, "radius"),
				&object->props.sphere.radius) &&
			object->props.sphere.radius > 0);
}
