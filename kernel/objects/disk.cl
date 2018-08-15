/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 15:17:57 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/15 20:42:45 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		disk_intersect(
		local t_object *obj,
		float3 origin,
		float3 u,
		int *face)
{
	float			l_dot_n;
	float3			p;
	float			t;

	if (dot(u, obj->facing) > 0)
		*face = 1;
	else
		*face = 0;
	if (fabs(l_dot_n = dot(u, obj->facing)) < 1e-6)
		return (FLT_MAX);
	t = dot(obj->pos - origin, obj->facing) / l_dot_n;
	p = origin + u * t;
	if (dot(p - obj->pos, p - obj->pos)
			<= obj->props.sphere.radius * obj->props.sphere.radius)
		return (t);
	return (FLT_MAX);
}
