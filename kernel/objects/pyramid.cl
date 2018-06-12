/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pyramid.cl                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 14:23:48 by jloro             #+#    #+#             */
/*   Updated: 2018/06/05 14:23:50 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		face_triangle_intersect(
		float3 pos1,
		float3 pos2,
		float3 pos3,
		float3 origin,
		float3 u
		)
{
	float	det;
	float3	facing;
	float3	v0v1;
	float3	v0v2;
	float3	vec1;
	float	w;
	float	v;

	facing = normalize(cross(pos2 - pos1, pos3 - pos1));
	if (fabs(dot(u, facing)) < 0)
		return (FLT_MAX);
	v0v1 = pos2 - pos1;
	v0v2 = pos3 - pos1;
	vec1 = cross(u, v0v2);
	det = dot(v0v1, vec1);
	if (fabs(det) < 0)
		return (FLT_MAX);
	det = 1 / det;
	w = dot(origin - pos1, vec1) * det;
	if (w < 0 || w > 1)
		return (FLT_MAX);
	v = dot(u, (vec1 = cross(origin - pos1, v0v1))) * det;
	if (v < 0 || v + w > 1)
		return (FLT_MAX);
	return (dot(v0v2, vec1) * det);
}

static float		face_paral_intersect(
		float3 pos1,
		float3 pos2,
		float3 pos3,
		float3 origin,
		float3 u
		)
{
	float	det;
	float3	facing;
	float3	v0v1;
	float3	v0v2;
	float3	vec1;
	float	w;
	float	v;

	facing = normalize(cross(pos2 - pos1, pos3 - pos1));
	if (fabs(dot(u, facing)) < 0)
		return (FLT_MAX);
	v0v1 = pos2 - pos1;
	v0v2 = pos3 - pos1;
	vec1 = cross(u, v0v2);
	det = dot(v0v1, vec1);
	if (fabs(det) < 0)
		return (FLT_MAX);
	det = 1 / det;
	w = dot(origin - pos1, vec1) * det;
	if (w < 0 || w > 1)
		return (FLT_MAX);
	v = dot(u, (vec1 = cross(origin - pos1, v0v1))) * det;
	if (v < 0 || v > 1)
		return (FLT_MAX);
	return (dot(v0v2, vec1) * det);
}

static float2		negative_pyramid_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u
		)
{
	int3	faces[5];
	float	t;
	float	tmax;
	float	t_tmp;
	int		i;

	faces[0] = (int3)(4, 3, 1);
	faces[1] = (int3)(0, 1, 4);
	faces[2] = (int3)(2, 0, 4);
	faces[3] = (int3)(2, 4, 3);
	faces[4] = (int3)(1, 0, 3);
	i = 0;
	t = FLT_MAX;
	tmax = 0;
	while (i < 5)
	{
		if (i == 4)
			t_tmp = face_paral_intersect(obj->props.pyramid.p[faces[i][0]],
obj->props.pyramid.p[faces[i][1]], obj->props.pyramid.p[faces[i][2]], origin, u);
		else
			t_tmp = face_triangle_intersect(obj->props.pyramid.p[faces[i][0]],
obj->props.pyramid.p[faces[i][1]], obj->props.pyramid.p[faces[i][2]], origin, u);
		if (t_tmp < t && t_tmp > 0)
			t = t_tmp;
		if (t_tmp > tmax && t_tmp > 0 && t_tmp != FLT_MAX)
			tmax = t_tmp;
		i++;
	}
	return ((float2)(t, tmax));
}

static float		pyramid_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u,
		int *face
		)
{
	int3	faces[5];
	float	t;
	float	t_tmp;
	int		face_tmp;
	int		i;

	faces[0] = (int3)(4, 3, 1);
	faces[1] = (int3)(0, 1, 4);
	faces[2] = (int3)(2, 0, 4);
	faces[3] = (int3)(2, 4, 3);
	faces[4] = (int3)(1, 0, 3);
	i = 0;
	t = FLT_MAX;
	while (i < 5)
	{
		if (i == 4)
			t_tmp = face_paral_intersect(obj->props.pyramid.p[faces[i][0]],
obj->props.pyramid.p[faces[i][1]], obj->props.pyramid.p[faces[i][2]], origin, u);
		else
			t_tmp = face_triangle_intersect(obj->props.pyramid.p[faces[i][0]],
obj->props.pyramid.p[faces[i][1]], obj->props.pyramid.p[faces[i][2]], origin, u);
		face_tmp = i;
		if (t_tmp < t && t_tmp > 0)
		{
			t = t_tmp;
			*face = face_tmp;
		}
		i++;
	}
	return (t);
}

static void			pyramid_normal(
		constant t_object *o,
		t_rt_result *r,
		int face
		)
{
	if (face == 0)
		r->normal = normalize(cross(o->props.pyramid.p[3] - o->props.pyramid.p[4],
					o->props.pyramid.p[1] - o->props.pyramid.p[4]));
	else if (face == 1)
		r->normal = normalize(cross(o->props.pyramid.p[1] - o->props.pyramid.p[4],
					o->props.pyramid.p[0] - o->props.pyramid.p[4]));
	else if (face == 2)
		r->normal = normalize(cross(o->props.pyramid.p[0] - o->props.pyramid.p[4],
					o->props.pyramid.p[2] - o->props.pyramid.p[4]));
	else if (face == 3)
		r->normal = normalize(cross(o->props.pyramid.p[2] - o->props.pyramid.p[4],
					o->props.pyramid.p[3] - o->props.pyramid.p[4]));
	else if (face == 4)
		r->normal = -o->facing;
}
