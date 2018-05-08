/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 23:16:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/08 04:40:47 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

t_hitlst			*sphere_intersect(t_object *o, t_vec3f *cam, t_vec3f *u)
{
	float			delta;
	t_vec3f			v[3];
	float			i[2];
	t_hitlst		*lst;

	i[0] = vec3f_dot_product(u, vec3f_sub(cam, &o->pos, v));
	i[1] = vec3f_norm(v);
	delta = i[0] * i[0] - i[1] * i[1] +
		o->props.sphere.radius * o->props.sphere.radius;
	if (delta < 0)
		return (NULL);
	if (delta == 0)
		lst = hitlstnew(o, -i[0], vec3f_mul(v, -i[0], &v[1]),
				vec3f_sub(v, &o->pos, &v[2]));
	else if (delta > 0)
	{
		i[1] = (float)sqrt(delta);
		lst = hitlstnew(o, -i[0] + i[1], vec3f_mul(v, -i[0] + i[1], &v[1]),
				vec3f_sub(v, &o->pos, &v[2]));
		if (lst)
			lst->next = hitlstnew(o, -i[0] - i[1], vec3f_mul(
						v, -i[0] - i[1], &v[1]), vec3f_sub(v, &o->pos, &v[2]));
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
