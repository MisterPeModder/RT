/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:04:43 by jhache            #+#    #+#             */
/*   Updated: 2018/05/29 11:03:34 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** cone_intersect: Calculates the distance between the intersection
**                 of the ray and the cone and the ray origin.
**
** -obj: the cone object
** -origin: the starting postion of the ray
** -u: the ray's unit vector
**
** returns: the distance, if an intersectection point has been found.
**          Returns FLT_MAX otherwise.
*/

static float		cone_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u
		)
{
	float			a;
	float			b;
	float			c;
	float			delta;
	float3			tmp;

	tmp = origin - obj->pos;
	c = cos(obj->props.cone.opening_angle);
	c *= c;
	a = pow(dot(u, obj->facing), 2) - c;
	b = 2 * (dot(u, obj->facing) * dot(tmp, obj->facing) - dot(u, tmp) * c);
	c = dot(tmp, obj->facing) * dot(tmp, obj->facing) - dot(tmp, tmp) * c;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (FLT_MAX);
	else if (delta == 0)
		return (-b / (2 * a));
	c = (-b - sqrt(delta)) / (2 * a);
	a = (-b + sqrt(delta)) / (2 * a);
	c = c > a ? a : c;
	return (a > 0 ? a : c);
}

static void			cone_normal(
		constant t_object *o,
		t_rt_result *r
		)
{
	float3			vs;
	float3			n;
	float			s;
	float3			v;

	vs = r->pos - o->pos;
	s = length(vs);
	n = o->facing;
	if (dot(o->facing, vs) < 0)
		n = -n;
	v = n * (s / cos(o->props.cone.opening_angle));
	v += o->pos;
	r->normal = normalize(r->pos - v);
}
