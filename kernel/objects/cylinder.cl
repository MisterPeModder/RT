/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:43:30 by jhache            #+#    #+#             */
/*   Updated: 2018/06/01 13:41:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float				cylinder_intersect2(
		constant t_object *obj,
		float3 origin,
		float3 u,
		int i,
		int *face
		)
{
	float3			tmp;
	float3			tmp2;
	float			a;

	if (i == 1)
		tmp = obj->pos + obj->props.cylinder.len / 2 * obj->facing;
	else
		tmp = obj->pos - obj->props.cylinder.len / 2 * obj->facing;
	a = dot(tmp - origin, obj->facing) / dot(u, obj->facing);
	tmp2 = origin + u * a;
	if (dot(tmp2 - tmp, tmp2 - tmp) <= obj->props.cylinder.radius * obj->props.cylinder.radius && a > 1e-6)
	{
		*face = i;
		return (a);
	}
	return (FLT_MAX);
}

static float				cylinder_intersect3(
		constant t_object *obj,
		float3 origin,
		float3 u,
		float c,
		int *face
		)
{
	float	a;
	float	dist;
	float	dist1;

	dist = length(origin - obj->pos + obj->props.cylinder.len / 2 * obj->facing);
	dist1 = length(origin - obj->pos - obj->props.cylinder.len / 2 * obj->facing);
	a = dot(u, obj->facing) * c + dot(origin - obj->pos, obj->facing);
	if ((a < 0 - obj->props.cylinder.len / 2 || a > obj->props.cylinder.len
				/ 2) && obj->props.cylinder.len != -1)
	{
		if (dist > dist1 && (a = cylinder_intersect2(obj, origin, u, 1, face)) != FLT_MAX)
			return (a);
		else if ((a = cylinder_intersect2(obj, origin, u, 2, face)) != FLT_MAX)
			return (a);
		return (FLT_MAX);
	}
	else
		return (c);
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

static float				cylinder_intersect(
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
	if (delta < 0)
		return (FLT_MAX);
	else if (delta == 0)
		return (-b / (2 * a));
	c = (-b - sqrt(delta)) / (2 * a);
	a = (-b + sqrt(delta)) / (2 * a);
	c = c > a ? a : c;
	*face = 0;
	return (cylinder_intersect3(obj, origin, u, c, face));
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

void				cylinder_normal(
		constant t_object *o,
		t_rt_result *r,
		int face
		)
{
	float3			h_pos;

	if (face == 0)
	{
		h_pos = o->facing * dot(r->pos - o->pos, o->facing) + o->pos;
		r->normal = normalize(r->pos - h_pos);
	}
	else if (face == 2)
		r->normal = -o->facing;
	else if (face == 1)
		r->normal = o->facing;
}
