/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:43:30 by jhache            #+#    #+#             */
/*   Updated: 2018/06/20 17:56:02 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float				cylinder_intersect3(
		constant t_object *obj,
		float3 origin,
		float3 u,
		float2 c,
		int *face
		)
{
	float	a;
	float3	tmp;
	float3	tmp2;
	float2	inter;
	float	result;
	float	test;

	a = dot(u, obj->facing) * c.x + dot(origin - obj->pos, obj->facing);
	test = dot(obj->pos - origin, obj->facing);
	if (obj->props.cylinder.len != -1
		&& ((a < 0 - obj->props.cylinder.len / 2
				|| a > obj->props.cylinder.len / 2)
			|| ((test > 0 - obj->props.cylinder.len / 2
				&& test < obj->props.cylinder.len / 2) && c.x < 0)))
	{
		tmp = obj->pos + obj->props.cylinder.len / 2 * obj->facing;
		tmp2 = obj->pos - obj->props.cylinder.len / 2 * obj->facing;
		inter.x = dot(tmp - origin, obj->facing) / dot(u, obj->facing);
		inter.y = dot(tmp2 - origin, obj->facing) / dot(u, obj->facing);
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
		tmp2 = origin + u * result;
		if (dot(tmp2 - tmp, tmp2 - tmp) <= obj->props.cylinder.radius
				* obj->props.cylinder.radius)
		{
			if (dot(u, obj->facing) > 0)
				*face = ((*face == 1) ? 2 : 1);
			return (result);
		}
		if ((test > 0 - obj->props.cylinder.len / 2
				&& test < obj->props.cylinder.len / 2) && c.x < 0)
		{
			*face = 3;
			return (c.y);
		}
		return (FLT_MAX);
	}
	else if (obj->props.cylinder.len == -1 && c.x < 0 && c.y > 0)
	{
		*face = 3;
		return (c.y);
	}
	return (c.x);
}

/*
 ** cylinder_intersect: Calculates the distance between the intersection
 **                     of the ray and the cylinder and the ray origin.
 **
 ** -obj: the cylinder object
 ** -origin: the starting postion of the ray
 ** -u: the ray's unit vector
 **
 ** returns: the distance, if an intersection point has been found.
 **          Returns FLT_MAX otherwise.
 */

static float			cylinder_intersect(
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
	a = dot(u, obj->facing);
	a = dot(u, u) - a * a;
	b = 2 * (dot(u, tmp)
			- dot(u, obj->facing)
			* dot(tmp, obj->facing));
	c = dot(tmp, tmp)
		- pow(dot(tmp, obj->facing), 2)
		- obj->props.cylinder.radius * obj->props.cylinder.radius;
	delta = b * b - 4 * a * c;
	if (delta < 1e-6)
		return (FLT_MAX);
	else if (delta == 0)
		return (-b / (2 * a));
	c = (-b - sqrt(delta)) / (2 * a);
	a = (-b + sqrt(delta)) / (2 * a);
	b = c > a ? a : c;
	c = c > a ? c : a;
	*face = 0;
	return (cylinder_intersect3(obj, origin, u, (float2)(b, c), face));
}

/*
 ** cylinder_normal: Computes the normal vector at the intersection point.
 **
 ** formula:
 ** ph (vector) = hitpos - objpos
 ** hit_height = ph . axis
 ** h_pos = hit_height * axis
 ** normal = (hitpos - h_pos) normalized.
 **
 ** normal = hitpos - ((hitpos - objpos) . axis) * axis [normalized]
 */

static void				cylinder_normal(
		constant t_object *o,
		t_rt_result *r,
		int face
		)
{
	float3			h_pos;

	if (face == 0 || face == 3)
	{
		h_pos = o->facing * dot(r->pos - o->pos, o->facing) + o->pos;
		if (face == 0)
			r->normal = normalize(r->pos - h_pos);
		else
			r->normal = -normalize(r->pos - h_pos);
	}
	else if (face == 2)
		r->normal = -o->facing;
	else if (face == 1)
		r->normal = o->facing;
}
