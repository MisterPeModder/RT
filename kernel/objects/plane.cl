/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:56:10 by jhache            #+#    #+#             */
/*   Updated: 2018/08/15 20:43:36 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		plane_intersect(
		local t_object *obj,
		float3 origin,
		float3 u,
		int *face
		)
{
	float			l_dot_n;

	*face = dot(u, obj->facing) > 0;
	if (fabs(l_dot_n = dot(u, obj->facing)) < 0.000001)
		return (FLT_MAX);
	return (dot((obj->pos - origin), obj->facing) / l_dot_n);
}

static void			plane_normal(
		local t_object *o,
		t_rt_result *r,
		int face
		)
{
	r->normal = (face ? -o->facing : o->facing);
}
