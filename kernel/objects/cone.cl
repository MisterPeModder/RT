/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:04:43 by jhache            #+#    #+#             */
/*   Updated: 2018/08/20 15:10:52 by jhache           ###   ########.fr       */
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
	a = dot(tmp - origin, -obj->facing) / dot(u, -obj->facing);
	tmp2 = u * a + origin;
	if (dot(tmp2 - tmp, tmp2 - tmp) <=
			pow(tan(obj->props.cone.opening_angle)
				* length(tmp - obj->pos), 2) && a > 0)
	{
		*face = dot(u, -obj->facing) > 0 ? 1 : 2;
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
	float2			inter;
	float			result;

	result = dot(u, obj->facing);
	tmp = obj->pos + obj->props.cone.len / 2 * obj->facing;
	tmp2 = obj->pos - obj->props.cone.len / 2 * obj->facing;
	inter.x = dot(tmp - origin, obj->facing) / result;
	inter.y = dot(tmp2 - origin, -obj->facing) / dot(u, -obj->facing);
	if ((inter.x < 0 || inter.y < inter.x) && inter.y > 0)
	{
		result = inter.y;
		tmp = tmp2;
		*face = 2;
	}
	else if (inter.x > 0)
	{
		result = inter.x;
		*face = 1;
	}
	else
		return (FLT_MAX);
	tmp2 = u * result + origin;
	if (dot(tmp2 - tmp, tmp2 - tmp) <=
			pow(tan(obj->props.cone.opening_angle)
				* length(tmp - obj->pos), 2))
	{
		tmp = (*face == 1) ? obj->facing : -obj->facing;
		if (dot(u, tmp) > 0)
			*face = ((*face == 1) ? 2 : 1);
		return (result);
	}
	return (FLT_MAX);
}

static float		cone_intersect2(
		constant t_object *obj,
		float3 origin,
		float3 u,
		float3 c,
		int *face
		)
{
	float2	tmp;
	float	test;
	float	test_rad;
	int		test_rad_bool;

	*face = 0;
	test = dot(origin - obj->pos, obj->facing);
	test_rad = test / length(origin - obj->pos);
	test_rad = fabs(test_rad);
	test_rad_bool = test_rad > cos(obj->props.cone.opening_angle);
	tmp.y = dot(u, obj->facing) * c.z +
		dot(origin - obj->pos, obj->facing);
	if (obj->props.cone.simple)
	{
		if (obj->props.cone.len == -1)
		{
			if (tmp.y > 0 && c.x > 0)
				return (FLT_MAX);
			if (tmp.y < 0 && c.x > 0)
				return (c.z);
			if (test_rad_bool)
				*face = 3;
			return (c.y);
		}
		tmp.x = cone_intersect_simple(obj, origin, u, face);
		if ((tmp.y > 0 || fabs(tmp.y) > obj->props.cone.len) &&
				(c.x > 0 || fabs(c.x) > obj->props.cone.len) &&
				!(test > -obj->props.cone.len && test < 0
					&& test_rad_bool))
			return (FLT_MAX);
		if (test > 0 && test_rad_bool)
		{
			*face = 0;
			return (c.z);
		}
		if ((fabs(c.x) > obj->props.cone.len || c.y > tmp.x || c.y < 1e-6))
			return (tmp.x);
		if (test > -obj->props.cone.len && test < 0
					&& test_rad_bool)
			*face = 3;
		else
			*face = 0;
		return (c.y);
	}
	else
	{
		if (obj->props.cone.len == -1)
		{
			if (test_rad_bool)
				*face = 3;
			return (c.y);
		}
		tmp.x = cone_intersect_double(obj, origin, u, face);
		if (fabs(tmp.y) < obj->props.cone.len / 2 && tmp.x == FLT_MAX
				&& fabs(test) > obj->props.cone.len / 2
				&& test_rad_bool)
		{
			*face = 0;
			return (c.z);
		}
		if (fabs(c.x) > obj->props.cone.len / 2
			|| c.y > tmp.x || c.y < 1e-6)
			return (tmp.x);
		if (fabs(test) < obj->props.cone.len / 2
					&& test_rad_bool)
			*face = 3;
		else
			*face = 0;
		return (c.y);
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
	float			a;
	float			b;
	float			c;
	float			delta;
	float3			tmp;

	tmp = origin - obj->pos;
	c = cos(obj->props.cone.opening_angle);
	c *= c;
	a = pow(dot(u, obj->facing), 2) - c;
	b = 2 * (dot(u, obj->facing)
			* dot(tmp, obj->facing)
			- dot(u, tmp) * c);
	c = dot(tmp, obj->facing)
		* dot(tmp, obj->facing)
		- dot(tmp, tmp) * c;
	delta = b * b - 4 * a * c;
	if (delta < 1e-6)
		return (FLT_MAX);
	else if (delta == 0)
		return (-b / (2 * a));
	c = (-b - sqrt(delta)) / (2 * a);
	a = (-b + sqrt(delta)) / (2 * a);
	delta = c > a ? a : c;
	b = c > a ? c : a;
	c = delta < 0 ? b : delta;
	a = dot(u, obj->facing) * c +
		dot(origin - obj->pos, obj->facing);
	return (cone_intersect2(obj, origin, u, (float3)(a, c, b), face));
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

	if (face == 0 || face == 3)
	{
		s = length(r->pos - o->pos);
		n = o->facing;
		if (dot(n, r->pos - o->pos) < 0)
			n = -n;
		v = s / cos(o->props.cone.opening_angle) * n + o->pos;
		if (face == 0)
			r->normal = normalize(r->pos - v);
		else
			r->normal = -normalize(r->pos - v);
	}
	else if (face == 1)
		r->normal = o->facing;
	else
		r->normal = -o->facing;
}
