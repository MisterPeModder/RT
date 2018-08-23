/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 07:14:24 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/23 07:54:13 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include <json.h>
# include "ocl_types.h"
# include "ocl_common_structs.h"

struct s_scene;

struct s_arrlst;

typedef struct		s_face
{
	int				*verts;
	int				verts_num;
}					t_face;

typedef struct		s_mesh_data
{
	t_face			*faces;
	t_clfloat3		*vertices;
	t_clfloat3		angle;
	int				faces_num;
	float			scale;
}					t_mesh_data;

/*
** parse_mesh: Parses mesh.
*/
int					parse_mesh(struct s_scene *scene, t_object *object,
		const t_json_object *data);

/*
** parse_json_mesh: Parses mesh from JSON format.
*/
int					parse_json_mesh(struct s_scene *scene, t_object *object,
		const t_json_object *data);

/*
** parse_wobj_mesh: Parses mesh from OBJ format.
*/
int					parse_wobj_mesh(struct s_scene *scene, t_object *object,
		const t_json_object *data);

/*
** mesh_load: Separates faces to triangles and stores them into 'triangles'.
**
** -triangles: a pointer to the array of triangles that will be created.
** -data: contains the data from parsed from the source file.
*/
int					mesh_load(struct s_scene *scene, t_mesh_data *data,
		t_object *object);

/*
** Parses a 'v' command form OBJ format.
**
** -line: The source line, it must start with 'v'.
** -vertices: The list of vertices, its element type is t_clfloat3.
*/
int					parse_wobj_vertex(const char *line,
		struct s_arrlst *vertices);

/*
** Parses a 'f' command form OBJ format.
**
** -line: The source line, it must start with 'f'.
** -vertices: The list of faces, its element type is t_face.
*/
int					parse_wobj_face(const char *line, struct s_arrlst *faces);

#endif
