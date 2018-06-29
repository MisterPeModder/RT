/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow_ray.cl                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 20:42:03 by jhache            #+#    #+#             */
/*   Updated: 2018/06/29 11:34:18 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 ** shadow_raytrace: Handles the shadow ray tracing operation.
 **
 ** -scene: the scene instance.
 ** -o: origin of the ray.
 ** -u: unit vector (direction) of that ray.
 ** -r: where the result will be stored.
 **
 ** returns: 1 if an intersection has been found, 0 otherwise.
 */

static int			shadow_raytrace(
		constant t_object *objs,
		constant t_mesh_triangle *triangles,
		size_t objs_num,
		float3 o,
		float3 u,
		t_rt_result *r,
		char no_negative,
		float dist_max
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
	d = dist_max;
	r->shadow_amount = (float3)(1.f, 1.f, 1.f);
	while (i < objs_num)
	{
		tmp = 0;
		if (objs[i].mat.props == MAT_PORTAL || !objs[i].mat.has_shadow)
		{
			++i;
			continue ;
		}
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
		if (tmp == FLT_MAX)
			tmp = dist_max;
		else if (tmp < dist_max && tmp > 0.f)
			r->shadow_amount *= ((objs[i].mat.props == MAT_REFRACTIVE)
					? objs[i].color * objs[i].mat.props_coef * 0.6f : -1.f);
		if (r->shadow_amount.x < 0.f)
			return (1);
		if (tmp > 0 && tmp < d)
		{
			r->obj = objs + i;
			d = tmp;
			face = face_tmp;
		}
		++i;
	}
	if (d == dist_max)
		return (0);
	r->dist = d;
	r->pos = u * d + o;
	return (1);
}
