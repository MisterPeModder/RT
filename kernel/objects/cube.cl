/* **************************************************************************** */
/*                                                                              */
/*                                                         :::      ::::::::    */
/*    cube.cl                                            :+:      :+:    :+:    */
/*                                                     +:+ +:+         +:+      */
/*    By: jloro <marvin@42.fr>                       +#+  +:+       +#+         */
/*                                                 +#+#+#+#+#+   +#+            */
/*    Created: 2018/06/06 13:18:17 by jloro             #+#    #+#              */
/*    Updated: 2018/06/06 13:18:17 by jloro            ###   ########.fr        */
/*                                                                              */
/* **************************************************************************** */

static float		face_intersect(
		float3 pos1,
		float3 pos2,
		float3 pos3,
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

	facing = normalize(cross(pos2 - pos1, pos3 - pos1));
	if (fabs(dot(u, facing)) < 1e-6)
		return (FLT_MAX);
	if (dot(u, facing) > 1e-6)
		*face = 1;
	else
		*face = 0;
	v0v1 = pos2 - pos1;
	v0v2 = pos3 - pos1;
	vec1 = cross(u, v0v2);
	det = dot(v0v1, vec1);
	if (fabs(det) < 1e-6)
		return (FLT_MAX);
	det = 1 / det;
	w = dot(origin - pos1, vec1) * det;
	if (w < 1e-6 || w > 1 + 1e-6)
		return (FLT_MAX);
	v = dot(u, (vec1 = cross(origin - pos1, v0v1))) * det;
	if (v < 1e-6 || v > 1 + 1e-6)
		return (FLT_MAX);
	return (dot(v0v2, vec1) * det);
}

static float		cube_intersect(
		constant t_object *obj,
		float3 origin,
		float3 u,
		int *face
		)
{
	int3	faces[6];
	float	t;
	float	t_tmp;
	int	face_tmp;
	int	i;

	faces[0] = (int3)(4, 7, 1);//HAUT
	faces[1] = (int3)(2, 3, 5);//BAS
	faces[2] = (int3)(1, 4, 2);//DROITE
	faces[3] = (int3)(0, 7, 3);//GAUCHE
	faces[4] = (int3)(4, 7, 5);//DERRIERE
	faces[5] = (int3)(1, 0, 2);//DEVANT
	i = 0;
	t = FLT_MAX;
	while (i < 6)
	{
		t_tmp = face_intersect(obj->props.cube.p[faces[i][0]], obj->props.cube.p[faces[i][1]], obj->props.cube.p[faces[i][2]], origin, u, &face_tmp);
		face_tmp += i * 10;
		if (t_tmp < t && t_tmp > 0)
		{
			t = t_tmp;
			*face = face_tmp;
		}
		i++;
	}
	return (t);
}

static void			cube_normal(
		constant t_object *o,
		t_rt_result *r,
		int face
		)
{
	if (face / 10 == 0 && face % 10 == 0)
		r->normal = o->facing;
	else if (face / 10 == 0 && face % 10 == 1)
		r->normal = -o->facing;
	else if (face / 10 == 1 && face % 10 == 0)
		r->normal = -o->facing;
	else if (face / 10 == 1 && face % 10 == 1)
		r->normal = o->facing;
	else if (face / 10 == 2 && face % 10 == 0)
		r->normal = -o->right;
	else if (face / 10 == 2 && face % 10 == 1)
		r->normal = o->right;
	else if (face / 10 == 3 && face % 10 == 0)
		r->normal = -o->right;
	else if (face / 10 == 3 && face % 10 == 1)
		r->normal = o->right;
	else if (face / 10 == 4 && face % 10 == 0)
		r->normal = o->dir;
	else if (face / 10 == 4 && face % 10 == 1)
		r->normal = -o->dir;
	else if (face / 10 == 5 && face % 10 == 0)
		r->normal = o->dir;
	else if (face / 10 == 5 && face % 10 == 1)
		r->normal = -o->dir;

}
