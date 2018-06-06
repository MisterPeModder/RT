/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.cl                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 14:23:48 by jloro             #+#    #+#             */
/*   Updated: 2018/06/05 14:23:50 by jloro            ###   ########.fr       */
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
	float3	facing;
	float3	v0v1;
	float3	v0v2;
	float3	vec1;
	float	w;
	float	v;

	facing = normalize(cross(obj->props.triangle.pos2 - obj->pos,
			obj->props.triangle.pos1 - obj->pos));
	if (fabs(dot(u, facing)) < 1e-6)
		return (FLT_MAX);
	if (dot(u, facing) > 0)
		*face = 1;
	else
		*face = 0;
	v0v1 = obj->props.triangle.pos1 - obj->pos;
	v0v2 = obj->props.triangle.pos2 - obj->pos;
	vec1 = cross(u, v0v2);
	det = dot(v0v1, vec1);
	if (fabs(det) < 1e-6)
		return (FLT_MAX);
	det = 1 / det;
	w = dot(origin - obj->pos, vec1) * det;
	if (w < 1e-6 || w > 1 + 1e-6)
		return (FLT_MAX);
	v = dot(u, (vec1 = cross(origin - obj->pos, v0v1))) * det;
	if (v < 1e-6 || w + v > 1 + 1e-6)
		return (FLT_MAX);
	return (dot(v0v2, vec1) * det);
}

static void			triangle_normal(
		constant t_object *o,
		t_rt_result *r,
		int face
		)
{
	if (face)
		r->normal = -normalize(cross(o->props.triangle.pos2 - o->pos,
			o->props.triangle.pos1 - o->pos));
	else
		r->normal = normalize(cross(o->props.triangle.pos2 - o->pos,
			o->props.triangle.pos1 - o->pos));

}
