/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:43:30 by jhache            #+#    #+#             */
/*   Updated: 2018/05/28 22:28:56 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

float				cylinder_intersect(__local t_object *obj, float3 origin,
		float3 u)
{
	float			a;
	float			b;
	float			c;
	float			delta;
	float3			tmp;

	tmp = origin - obj->pos;
	a = dot(u, obj->facing);
	a = dot(u, u) - a * a;
	b = 2 * (dot(u, tmp) - dot(u, obj->facing) * dot(tmp, obj->facing));
	c = dot(tmp, tmp) - pow(dot(tmp, obj->facing), 2)
		- obj->props.cylinder.radius * obj->props.cylinder.radius;
	delta = b * b - 4 * a * c;
	if (delta < 0)
		return (FLT_MAX);
	else if (delta == 0)
		return (-b / (2 * a));
	c = (-b - sqrt(delta)) / (2 * a);
	a = (-b + sqrt(delta)) / (2 * a);
	c = c > a ? a : c;
	return (c);
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

void				cylinder_normal(__local t_object *o, t_rt_result *r)
{
	float3			ph;
	float3			h_pos;

	ph = r->pos -o->pos;
	h_pos = o->facing * dot(ph, o->facing) + o->pos;
	r->normal = normalize(r->pos - h_pos);
}
