/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meshes.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 14:23:48 by jloro             #+#    #+#             */
/*   Updated: 2018/08/20 15:11:27 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float	face_triangle_intersect(
		float3 pos1,
		float3 pos2,
		float3 pos3,
		float3 facing,
		float3 origin,
		float3 u
		)
{
	float	det;
	float3	v0v1;
	float3	v0v2;
	float3	vec1;
	float	w;
	float	v;

	if (fabs(dot(u, facing)) < 0)
		return (FLT_MAX);
	v0v1 = pos2 - pos1;
	v0v2 = pos3 - pos1;
	vec1 = cross(u, v0v2);
	det = dot(v0v1, vec1);
	det = 1 / det;
	w = dot(origin - pos1, vec1) * det;
	if (w < 1e-6 || w > 1 + 1e-6)
		return (FLT_MAX);
	v = dot(u, (vec1 = cross(origin - pos1, v0v1))) * det;
	if (v < 1e-6 || v + w > 1 + 1e-6)
		return (FLT_MAX);
	return (dot(v0v2, vec1) * det);
}

static float		mesh_intersect(
		constant t_object *obj,
		constant t_mesh_triangle *triangles,
		float3 origin,
		float3 u,
		int *face,
		size_t *index
		)
{
	float	t;
	float	tmin;
	float	t_tmp;
	int		face_tmp;
	size_t	i;

	i = *index;
	t = FLT_MAX;
	tmin = FLT_MAX;
	while (i < obj->props.mesh.num_triangles + *index)
	{
		t_tmp = face_triangle_intersect(triangles[i].p1, triangles[i].p2, triangles[i].p3,
				triangles[i].facing, origin, u);
		face_tmp = i;
		if (t_tmp < t && t_tmp > 0)
		{
			t = t_tmp;
			*face = face_tmp;
		}
		if (t_tmp < tmin)
			tmin = t_tmp;
		i++;
	}
	if (tmin < 0)
		*face *= -1;
	*index += obj->props.mesh.num_triangles;
	return (t);
}

static void			mesh_normal(
		constant t_mesh_triangle *triangles,
		t_rt_result *r,
		int face
		)
{
	if (face >= 0)
		r->normal = triangles[abs(face)].facing;
	else
		r->normal = -triangles[abs(face)].facing;
}
