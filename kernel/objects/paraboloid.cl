/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 14:23:48 by jloro             #+#    #+#             */
/*   Updated: 2018/08/15 20:43:22 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		paraboloid_intersect(
		local t_object *obj,
		float3 origin,
		float3 u
		)
{
	float	a;
	float	b;
	float	c;
	float3	x;
	float	delta;

	x = origin - obj->pos;
	a = dot(u, u) - pow(dot(u, obj->facing), 2);
	b = 2 * (dot(u, x) - dot (u, obj->facing) *
			(dot(x, obj->facing) + 2 * 0.5));
	c = dot(x, x) - dot (x, obj->facing) *
			(dot(x, obj->facing) + 4 * 0.5);
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

static void			paraboloid_normal(
		local t_object *o,
		t_rt_result *r
		)
{
	r->normal = normalize(r->pos - o->pos - o->facing *
			(o->props.paraboloid.len + dot(r->pos - o->pos, o->facing)));
}
