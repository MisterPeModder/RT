/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:56:10 by jhache            #+#    #+#             */
/*   Updated: 2018/06/01 13:47:55 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		plane_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u,
		int *face
		)
{
	float			l_dot_n;

	if (dot(u, obj->facing) > 0)
		*face = 1;
	else
		*face = 0;
	if (fabs(l_dot_n = dot(u, obj->facing)) < 0.000001)
		return (FLT_MAX);
	return (dot((obj->pos - origin), obj->facing) / l_dot_n);
}

static void			plane_normal(
		constant t_object *o,
		t_rt_result *r,
		int face
		)
{
	if (face)
		r->normal = -o->facing;
	else
		r->normal = o->facing;
}
