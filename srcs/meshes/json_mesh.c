/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/13 22:09:15 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/21 20:13:39 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include "mesh.h"
#include "rt.h"

static t_clfloat3	*parse_json_vertices(const t_json_value *data,
		size_t *verts_num)
{
	t_clfloat3		*verts;
	size_t			i;

	if (!data || data->arr.type != JSON_ARRAY
			|| !(verts = malloc(sizeof(t_clfloat3) * data->arr.values_num)))
		return (NULL);
	i = 0;
	while (i < data->arr.values_num)
	{
		if (!(vec3f_from_json(data->arr.values[i], &verts[i])))
		{
			free(verts);
			return (NULL);
		}
		++i;
	}
	*verts_num = data->arr.values_num;
	return (verts);
}

static int			parse_json_face(t_face *face, const t_json_value *data,
		size_t verts_num)
{
	size_t			i;

	if (!data || data->arr.type != JSON_ARRAY
			|| !(face->verts = malloc(sizeof(int) * data->arr.values_num)))
		return (0);
	i = 0;
	while (i < data->arr.values_num)
	{
		if (!data->arr.values[i] || data->arr.values[i]->n_i.type != JSON_INT
				|| (size_t)data->arr.values[i]->n_i.value >= verts_num)
		{
			free(face->verts);
			return (0);
		}
		face->verts[i] = data->arr.values[i]->n_i.value;
		++i;
	}
	face->verts_num = data->arr.values_num;
	return (1);
}

static t_face		*parse_json_faces(t_mesh_data *mesh,
		const t_json_value *data, size_t verts_num)
{
	t_face			*faces;
	size_t			i;

	if (!data || data->arr.type != JSON_ARRAY || !data->arr.values_num
			|| !(faces = malloc(sizeof(t_face) * data->arr.values_num)))
		return (NULL);
	i = 0;
	while (i < data->arr.values_num)
	{
		if (!parse_json_face(&faces[i], data->arr.values[i], verts_num))
		{
			while (i > 0)
			{
				free(faces[i - 1].verts);
				--i;
			}
			free(faces);
			return (NULL);
		}
		++i;
	}
	mesh->faces_num = data->arr.values_num;
	return (faces);
}

int			parse_json_mesh(struct s_scene *scene, t_object *object,
		const t_json_object *data)
{
	t_mesh_data		mesh;
	t_json_value	*tmp;
	size_t			verts_num;

	if ((tmp = json_obj_get(data, "scale")))
	{
		if (!(float_from_json(tmp, &mesh.scale)))
			return (0);
	}
	else
		mesh.scale = 1.f;
	if (!(mesh.vertices = parse_json_vertices(json_obj_get(data, "vertices"),
					&verts_num)))
		return (0);
	if (!(mesh.faces = parse_json_faces(&mesh, json_obj_get(data, "faces"),
					verts_num)))
	{
		free(mesh.vertices);
		return (0);
	}
	if (!(angle_from_json(json_obj_get(data, "angle"), &mesh.angle)))
		vec3cl_fill(&mesh.angle, 0, 0, 0);
	return (mesh_load(scene, &mesh, object));
}
