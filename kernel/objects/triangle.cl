/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 14:23:48 by jloro             #+#    #+#             */
/*   Updated: 2018/06/23 17:05:26 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		triangle_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u,
		int *face
		)
{
	float	det;
	float3	v0v1;
	float3	v0v2;
	float3	vec1;
	float	w;
	float	v;

	if (fabs(dot(u, obj->facing)) < 1e-6)
		return (FLT_MAX);
	*face = dot(u, obj->facing) > 0;
	v0v1 = obj->props.triangle.pos1 - obj->pos;
	v0v2 = obj->props.triangle.pos2 - obj->pos;
	vec1 = cross(u, v0v2);
	det = 1 / dot(v0v1, vec1);
	w = dot(origin - obj->pos, vec1) * det;
	if (w < 1e-6 || w > 1 + 1e-6)
		return (FLT_MAX);
	v = dot(u, (vec1 = cross(origin - obj->pos, v0v1))) * det;
	if (v < 1e-6 || w + v > 1 + 1e-6)
		return (FLT_MAX);
	return (dot(v0v2, vec1) * det);
}
