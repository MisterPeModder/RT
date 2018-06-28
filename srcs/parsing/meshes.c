/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meshes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 15:01:16 by jloro             #+#    #+#             */
/*   Updated: 2018/06/28 19:12:42 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <stdio.h>
#include <libft_base/memory.h>

int					multiple_mesh(t_scene *scene, size_t *len)
{
	t_mesh_triangle	*temp;

	if (!(temp = ft_memdup((void*)scene->mesh_triangle,
			sizeof(t_mesh_triangle) *
			(scene->triangle_total_num - len[len[0] + 1]))))
		return (0);
	free(scene->mesh_triangle);
	if (!(scene->mesh_triangle = (t_mesh_triangle*)malloc(
			sizeof(t_mesh_triangle) * scene->triangle_total_num)))
		return (0);
	ft_memcpy((void*)scene->mesh_triangle, (void*)temp,
			sizeof(t_mesh_triangle) *
			(scene->triangle_total_num - len[len[0] + 1]));
	free(temp);
	return (1);
}

void				fill_mesh_triangle(t_scene *scene, t_arrlst *triangles,
		int **faces, size_t i[3])
{
	t_clfloat3		tmp;
	t_clfloat3		tmp2;

	scene->mesh_triangle[i[2]].p1 =
		*((t_clfloat3**)triangles->elements)[faces[i[0]][0]];
	scene->mesh_triangle[i[2]].p2 =
		*((t_clfloat3**)triangles->elements)[faces[i[0]][i[1] + 1]];
	scene->mesh_triangle[i[2]].p3 =
		*((t_clfloat3**)triangles->elements)[faces[i[0]][i[1] + 2]];
	vec3cl_sub(&scene->mesh_triangle[i[2]].p2,
			&scene->mesh_triangle[i[2]].p1, &tmp);
	vec3cl_sub(&scene->mesh_triangle[i[2]].p3,
			&scene->mesh_triangle[i[2]].p1, &tmp2);
	vec3cl_cross(&tmp2, &tmp, &scene->mesh_triangle[i[2]].facing);
	vec3cl_normalize(&scene->mesh_triangle[i[2]].facing,
			&scene->mesh_triangle[i[2]].facing);
}

static int			mesh_faces2(t_arrlst *triangles,
		const t_json_array *data, size_t *len, int **faces)
{
	size_t			i;
	size_t			j;
	t_json_value	*tmp;

	i = 0;
	while (i < len[0])
	{
		if (!(tmp = json_arr_get(data, i)) || tmp->arr.type != JSON_ARRAY
				|| tmp->arr.values_num < 3)
			return (mesh_fail(triangles, faces, i, 0));
		len[1 + i] = tmp->arr.values_num;
		j = 0;
		if (!(faces[i] = (int *)malloc(sizeof(int) * tmp->arr.values_num)))
			return (mesh_fail(triangles, faces, i, 0));
		while (j < tmp->arr.values_num)
		{
			if (!int_from_json(json_arr_get(&tmp->arr, j), &faces[i][j])
					|| faces[i][j] < 0 || faces[i][j] >= (int)len[len[0] + 2])
				return (mesh_fail(triangles, faces, i, 0));
			++j;
		}
		++i;
	}
	return (1);
}

static int			mesh_faces(t_object *object, t_scene *scene,
		t_arrlst *triangles, const t_json_array *data)
{
	int				**faces;
	size_t			i;
	size_t			*len;

	if (!(len = (size_t *)malloc(sizeof(size_t) * (data->values_num + 3))))
		return (0);
	len[0] = data->values_num;
	if (!(faces = (int **)malloc(sizeof(int *) * len[0])))
		return (0);
	len[len[0] + 2] = scene->num_vertex;
	if (!mesh_faces2(triangles, data, len, faces))
		return (0);
	i = 0;
	object->props.meshes.num_triangles = 0;
	while (i < len[0])
	{
		object->props.meshes.num_triangles += len[1 + i] - 2;
		i++;
	}
	len[len[0] + 1] = object->props.meshes.num_triangles;
	scene->triangle_total_num += object->props.meshes.num_triangles;
	if (!create_triangle(scene, triangles, faces, len))
		return (0);
	mesh_face_free(faces, len[0]);
	free(len);
	return (1);
}

int					mesh_parse(t_scene *scene, t_object *object,
		const t_json_object *data)
{
	size_t			i;
	t_json_value	*tmp;
	t_clfloat3		vec;
	t_arrlst		*triangles;

	if (!(triangles = arrlst_new(0)))
		return (0);
	i = 0;
	if (!(tmp = json_obj_get(data, "vertices")) || tmp->arr.type != JSON_ARRAY)
		return (mesh_fail(triangles, NULL, 0, 1));
	scene->num_vertex = tmp->arr.values_num;
	while (i < tmp->arr.values_num)
	{
		if (!vec3f_from_json(json_arr_get(&tmp->arr, i), &vec) ||
				!calc_coord(&vec, object, triangles))
			return (mesh_fail(triangles, NULL, 0, 1));
		++i;
	}
	if (!(tmp = json_obj_get(data, "faces")) || tmp->arr.type != JSON_ARRAY ||
			!mesh_faces(object, scene, triangles, &tmp->arr))
		return (mesh_fail(triangles, NULL, 0, 1));
	arrlst_del(&triangles, NULL);
	return (1);
}
