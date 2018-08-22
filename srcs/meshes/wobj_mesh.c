/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wobj_mesh.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 04:28:27 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/22 07:19:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "rt.h"

#undef BUFF_SIZE
#include <libft_base/io.h>
#include <get_next_line.h>
#include <libft_base/character.h>
#include <libft_containers/array_list.h>

static int			has_cmd(const char *line, const char *cmd)
{
	while (*line && *cmd)
	{
		if (*line != *cmd)
			return (0);
		++line;
		++cmd;
	}
	return (ft_isspace(*line));
}

static int			parse_wobj_line(char *line,
		t_arrlst *faces, t_arrlst *vertices)
{
	int				offset;

	if (line && *line && *line != '#') {
		if (has_cmd(line, "v"))
			return (parse_wobj_vertex(line, vertices));
		else if (has_cmd(line, "f"))
			return (parse_wobj_face(line, faces));
		else if (!has_cmd(line, "mtllib") && !has_cmd(line, "usemtl")
				&& !has_cmd(line, "g") && !has_cmd(line, "s")
				&& !has_cmd(line, "vt") && !has_cmd(line, "vn"))
		{
			offset = 0;
			while (line[offset] && !ft_isspace(line[offset]))
				++offset;
			line[offset] = 0;
			ft_putstr_fd("Unsupported .obj command: ", STDERR_FILENO);
			ft_putendl_fd(line, STDERR_FILENO);
			return (0);
		}
	}
	return (1);
}

static int			parse_wobj_file(int file, t_mesh_data *mesh,
		t_arrlst *faces, t_arrlst *vertices)
{
	char			*line;

	while (get_next_line(file, &line) == 1)
	{
		if (!parse_wobj_line(line, faces, vertices))
		{
			free(line);
			return (0);
		}
		free(line);
	}
	mesh->faces = faces->elements;
	mesh->vertices = vertices->elements;
	mesh->faces_num = faces->size;
	return (1);
}

static int			parse_wobj_file_wrapper(int file, t_mesh_data *mesh)
{
	t_arrlst		*faces;
	t_arrlst		*vertices;

	faces = NULL;
	vertices = NULL;
	if (!(faces = arrlst_new(sizeof(t_face), 0)))
		return (0);
	if (!(vertices = arrlst_new(sizeof(t_clfloat3), 0)))
	{
		arrlst_del(&faces, NULL, NULL);
		return (0);
	}
	if (!parse_wobj_file(file, mesh, faces, vertices))
	{
		arrlst_del(&faces, NULL, NULL);
		arrlst_del(&vertices, NULL, NULL);
		return (0);
	}
	free(faces);
	free(vertices);
	return (1);
}

int					parse_wobj_mesh(t_scene *scene, t_object *object,
		const t_json_object *data)
{
	t_json_value	*tmp;
	int				file;
	t_mesh_data		mesh;

	if ((tmp = json_obj_get(data, "scale")))
	{
		if (!(float_from_json(tmp, &mesh.scale)))
			return (0);
	}
	else
		mesh.scale = 1.f;
	if (!(tmp = json_obj_get(data, "source"))
			|| tmp->str.type != JSON_STRING
			|| (file = safe_file_open(tmp->str.value)) == -1)
		return (0);
	if (!parse_wobj_file_wrapper(file, &mesh))
	{
		close(file);
		return (0);
	}
	close(file);
	if (!(angle_from_json(json_obj_get(data, "angle"), &mesh.angle)))
		vec3cl_fill(&mesh.angle, 0, 0, 0);
	return (mesh_load(scene, &mesh, object));
}
