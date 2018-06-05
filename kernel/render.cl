/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.cl                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 14:04:19 by jhache            #+#    #+#             */
/*   Updated: 2018/06/01 15:26:25 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static float3		compute_pixel_coor(constant t_cam *cam, unsigned int w,
		unsigned int h, unsigned int x, unsigned int y)
{
	float3			vec;
	float			fov;

	fov = tan(cam->fov / 2);
	vec.x = (2 * ((x + 0.5) / w) - 1) * w / (float)h * fov;
	vec.y = (1 - 2 * ((y + 0.5) / h)) * fov;
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
		size_t objs_num,
		float3 o,
		float3 u,
		t_rt_result *r
		)
{
	size_t			i;
	float			d;
	float			tmp;
	int				face;
	int				face_tmp;

	i = 0;
	d = FLT_MAX;
	while (i < objs_num)
	{
		switch (objs[i].type)
		{
			case OBJ_SPHERE:
				tmp = sphere_intersect(&objs[i], o, u);
				break;
			case OBJ_PLANE:
				tmp = plane_intersect(&objs[i], o, u);
				break;
			case OBJ_CONE:
				tmp = cone_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_CYLINDER:
				tmp = cylinder_intersect(&objs[i], o, u, &face_tmp);
				break;
			case OBJ_DISK:
				tmp = disk_intersect(&objs[i], o, u);
				break;
			default:
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
			sphere_normal(r->obj, r);
			break;
		case OBJ_PLANE:
		case OBJ_DISK:
			plane_normal(r->obj, r);
			break;
		case OBJ_CONE:
			cone_normal(r->obj, r, face);
			break;
		case OBJ_CYLINDER:
			cylinder_normal(r->obj, r, face);
			break;
	}
	return (1);
}

/*
** shading: Handles the shading using the Phong algorithm.
**
** -scene: the scene instance.
** -r: the primary ray's raytrace result.
** -c: where the color of the pixel will be stored.
*/

static float3		shading(
		constant t_object *objs, size_t objs_num,
		constant t_light *lights, size_t lights_num,
		t_rt_result *r
		)
{
	size_t			i;
	float3			lvec;
	t_rt_result		sink;
	float3			start;
	float3			result;

	i = 0;
	result = r->obj->color / 10;
	while (i < lights_num)
	{
		lvec = normalize(lights[i].pos - r->pos);
		start = r->pos + 0.001f * r->normal;
		if (!raytrace(objs, objs_num, start, lvec, &sink)
				|| length(lights[i].pos - r->pos) < sink.dist)
			colorize(&lights[i], lvec, r, &result);
		++i;
	}
	return (result);
}
