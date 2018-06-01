/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.cl                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/01 15:17:57 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/01 15:24:30 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		disk_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u)
{
	float			l_dot_n;
	float3			tmp;
	float3			p;
	float			t;
	float3			facing;

	if (dot(u, obj->facing) > 0)
		facing = -obj->facing;
	else
		facing = obj->facing;
	if (fabs(l_dot_n = dot(u, facing)) < 1e-6)
		return (FLT_MAX);
	t = dot(obj->pos - origin, facing) / l_dot_n;
	p = origin + u * t;
	if (dot(p - obj->pos, p - obj->pos)
			<= obj->props.sphere.radius * obj->props.sphere.radius)
		return (t);
	return (FLT_MAX);
}
