/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:04:19 by jhache            #+#    #+#             */
/*   Updated: 2018/07/03 08:20:41 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float		choose_ray_dir(unsigned int seed)
{
	seed = (seed * 0x5DEECE66DL + 0xBL) & ((1L << 48) - 1);
	return (fabs(native_cos((float)(seed >> 16))));
}

static float3		compute_pixel_coor(constant t_cam *cam, unsigned int w,
		unsigned int h, unsigned int x, unsigned int y, unsigned long seed)
{
	float3			vec;
	float			fov;
	float			dir;

	dir = choose_ray_dir(seed + x + y * x);
	fov = tan(cam->fov / 2);
	vec.x = (2 * ((x + dir) / w) - 1) * w / (float)h * fov;
	vec.y = (1 - 2 * ((y + dir) / h)) * fov;
	vec.z = -1;
	rotate_x(&vec, cam->angle.x);
	rotate_y(&vec, cam->angle.y);
	rotate_z(&vec, cam->angle.z);
	return (normalize(vec));
}

/*
** raytrace: Handles the ray tracing operation.
**
** -scene: the scene instance.
** -o: origin of the ray.
** -u: unit vector (direction) of that ray.
** -r: where the result will be stored.
**
** returns: 1 if an intersection has been found, 0 otherwise.
*/

static int			raytrace(
		constant t_object *objs,
		constant t_mesh_triangle *triangles,
		size_t objs_num,
		float3 o,
		float3 u,
		t_rt_result *r,
		char no_negative
		)
{
	size_t			i;
	float			d;
	float			tmp;
	int				face;
	int				face_tmp;
	float2			t_neg;
	size_t			n;
	size_t			index_tri;

	index_tri = 0;
	i = 0;
	d = FLT_MAX;
	face_tmp = 0;
	while (i < objs_num)
	{
		tmp = 0;
		switch (objs[i].type)
		{
			case OBJ_SPHERE:
				tmp = sphere_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_PLANE:
				tmp = plane_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_CONE:
				tmp = cone_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_CYLINDER:
				tmp = cylinder_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_DISK:
				tmp = disk_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_TRIANGLE:
				tmp = triangle_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_PARABOLOID:
				tmp = paraboloid_intersect(&objs[i], o, u);
				break;
			case OBJ_MESH:
				tmp = mesh_intersect(&objs[i], triangles, o, u, &face_tmp, &index_tri);
				break;
			default:
				tmp = FLT_MAX;
		}
		n = 0;
		if (!no_negative)
		{
			while (n < objs_num)
			{
				if (objs[n].mat.props == MAT_NEGATIVE)
				{
					switch (objs[n].type)
					{
						case OBJ_SPHERE:
							t_neg = negative_sphere_intersect(&objs[n], o, u);
							break;
						default:
							t_neg = (float2)(FLT_MAX, FLT_MAX);
					}
					if (tmp < t_neg[1] && tmp > t_neg[0])
						tmp = FLT_MAX;
				}
				n++;
			}
			if (objs[i].mat.props == MAT_NEGATIVE)
				tmp = FLT_MAX;
		}
		if (tmp > 0 && tmp < d)
		{
			r->obj = objs + i;
			d = tmp;
			face = face_tmp;
		}
		++i;
	}
	if (d == FLT_MAX)
		return (0);
	r->dist = d;
	r->pos = u * d + o;
	switch (r->obj->type)
	{
		case OBJ_SPHERE:
			sphere_normal(r->obj, r, face);
			break;
		case OBJ_DISK:
		case OBJ_TRIANGLE:
		case OBJ_PLANE:
			plane_normal(r->obj, r, face);
			break;
		case OBJ_CONE:
			cone_normal(r->obj, r, face);
			break;
		case OBJ_CYLINDER:
			cylinder_normal(r->obj, r, face);
			break;
		case OBJ_PARABOLOID:
			paraboloid_normal(r->obj, r);
			break;
		case OBJ_MESH:
			mesh_normal(triangles, r, face);
			break;
	}
	return (1);
}

/*
** shading: Handles the shading using the Phong algorithm.
**
** -objs: the chained list for every object in the scene.
** -lights: the chained list for every lights in the scene.
** -r: the primary ray's raytrace result.
** -result: where the color of the pixel will be stored.
*/
static float3			shading(
		constant t_object *objs, size_t objs_num,
		constant t_light *lights, size_t lights_num, t_rt_result *r,
		constant t_mesh_triangle *triangles,
		char no_negative
		)
{
	size_t			i;
	float3			lvec;
	float3			shadow_amount;
	float3			start;
	float3			result;
	float			light_dist;

	i = 0;
	result = r->obj->color / 10;
	while (i < lights_num)
	{
		lvec = lights[i].pos - r->pos;
		light_dist = length(lvec);
		lvec = normalize(lvec);
		start = r->pos + 0.001f * r->normal;
		if (!shadow_raytrace(objs, triangles, objs_num, start, lvec, &shadow_amount, no_negative, light_dist))
			colorize(&lights[i], lvec, r, &result, (float3)(1.f, 1.f, 1.f));
		else if (shadow_amount.x >= 0.f)
			colorize(&lights[i], lvec, r, &result, shadow_amount);
		++i;
	}
	return (result);
}
