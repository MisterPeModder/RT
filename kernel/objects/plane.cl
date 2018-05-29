/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:56:10 by jhache            #+#    #+#             */
/*   Updated: 2018/05/29 11:03:58 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		plane_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u
		)
{
	float			l_dot_n;

	if (fabs(l_dot_n = dot(u, obj->facing)) < 0.000001)
		return (FLT_MAX);
	return (dot((obj->pos - origin), obj->facing) / l_dot_n);
}

static void			plane_normal(
		constant t_object *o,
		t_rt_result *r
		)
{
	r->normal = o->facing;
}
