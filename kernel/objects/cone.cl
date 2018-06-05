/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:04:43 by jhache            #+#    #+#             */
/*   Updated: 2018/06/01 14:26:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		cone_intersect_simple(
		constant t_object *obj,
		float3 origin,
		float3 u,
		int *face
		)
{
	float3	tmp;
	float3	tmp2;
	float	a;

	tmp = obj->pos - obj->props.cone.len * obj->facing;
	a = dot(tmp - origin, obj->facing) / dot(u, obj->facing);
	tmp2 = u * a + origin;
	if (dot(tmp2 - tmp, tmp2 - tmp) <=
			pow(tan(obj->props.cone.opening_angle)
				* length(tmp - obj->pos), 2))
	{
		*face = 1;
		return (a);
	}
	return (FLT_MAX);
}

static float		cone_intersect_double(
		constant t_object *obj,
		float3 origin,
		float3 u,
		int *face
		)
{
	float3			tmp;
	float3			tmp2;
	float			a;
	float			a2;
	float			af;

	af = dot(u, obj->facing);
	tmp = obj->pos + obj->props.cone.len / 2 * obj->facing;
	a2 = dot(tmp - origin, obj->facing) / af;
	tmp2 = obj->pos - obj->props.cone.len / 2 * obj->facing;
	a = dot(tmp2 - origin, obj->facing) / af;
	if (a2 < a)
		af = a2 > 0 ? a2 : a;
	else
	{
		tmp = tmp2;
		af = a > 0 ? a : a2;
	}
	tmp2 = u * af + origin;
	if (dot(tmp2 - tmp, tmp2 - tmp) <=
			pow(tan(obj->props.cone.opening_angle)
				* length(tmp - obj->pos), 2))
	{
		*face = a2 < a ? 1 : 2;
		return (af);
	}
	return (FLT_MAX);
}

static float		cone_intersect2(
		constant t_object *obj,
		float3 origin,
		float3 u,
		float i[4],
		int *face
		)
{
	*face = 0;
	if (obj->props.cone.simple)
	{
		if (i[1] > 0)
			return (cone_intersect_simple(obj, origin, u, face));
		if (obj->props.cone.simple && obj->props.cone.len != -1 &&
				i[1] < 0 - obj->props.cone.len)
			return (cone_intersect_simple(obj, origin, u, face));
		return (i[4]);
	}
	else
	{
		if (obj->props.cone.len == -1)
			return (i[4]);
		if ((i[1] < 0 - obj->props.cone.len / 2 ||
				i[1] > obj->props.cone.len / 2))
			return (cone_intersect_double(obj, origin, u, face));
		i[3] = cone_intersect_double(obj, origin, u, face);
		return (i[4] < i[3] ? i[4] : i[3]);
	}
}

/*
 ** cone_intersect: Calculates the distance between the intersection
 **                 of the ray and the cone and the ray origin.
 **
 ** -obj: the cone object
 ** -origin: the starting postion of the ray
 ** -u: the ray's unit vector
 **
 ** note: the i[] variable holds the a, b, and c parameters of the quadratic.
 **
 ** returns: the distance, if an intersectection point has been found.
 **          Returns FLT_MAX otherwise.
 */

static float		cone_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u,
		int *face
		)
{
	float			i[5];
	float3			tmp;

	tmp = origin - obj->pos;
	i[2] = cos(obj->props.cone.opening_angle);
	i[2] *= i[2];
	i[0] = pow(dot(u, obj->facing), 2) - i[2];
	i[1] = 2 * (dot(u, obj->facing)
			* dot(tmp, obj->facing)
			- dot(u, tmp) * i[2]);
	i[2] = dot(tmp, obj->facing)
		* dot(tmp, obj->facing)
		- dot(tmp, tmp) * i[2];
	i[3] = i[1] * i[1] - 4 * i[0] * i[2];
	if (i[3] < 0)
		return (FLT_MAX);
	else if (i[3] == 0)
		return (-i[1] / (2 * i[0]));
	i[2] = (-i[1] - sqrt(i[3])) / (2 * i[0]);
	i[0] = (-i[1] + sqrt(i[3])) / (2 * i[0]);
	i[4] = i[2] > i[0] ? i[0] : i[2];
	i[4] = i[0] > 0 ? i[0] : i[4];
	i[1] = dot(u, obj->facing) * i[4] +
		dot(origin - obj->pos, obj->facing);
	return (cone_intersect2(obj, origin, u, i, face));
}

static void			cone_normal(
		constant t_object *o,
		t_rt_result *r,
		int face
		)
{
	float3			n;
	float			s;
	float3			v;

	if (face == 0)
	{
		s = length(r->pos - o->pos);
		n = o->facing;
		if (dot(o->facing, r->pos - o->pos) < 0)
			n = -n;
		v = s / cos(o->props.cone.opening_angle) * n + o->pos;
		r->normal = normalize(r->pos - v);
	}
	else if (face == 1)
		r->normal = -o->facing;
	else
		r->normal = o->facing;
}
