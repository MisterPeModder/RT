/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:58:37 by jhache            #+#    #+#             */
/*   Updated: 2018/05/29 11:04:13 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		sphere_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u
		)
{
	float	a;
	float	b;
	float	c;
	float	delta;
	float3	tmp;

	a = dot(u, u);
	tmp = origin - obj->pos;
	b = 2 * dot(u, tmp);
	c = dot(tmp, tmp) - obj->props.sphere.radius * obj->props.sphere.radius;
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

static void			sphere_normal(
		constant t_object *o,
		t_rt_result *r
		)
{
	r->normal = normalize(r->pos - o->pos);
}
