/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:29:09 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/23 07:38:44 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <json.h>
# include "ocl_common_structs.h"
# include "scene.h"

int					obj_make(t_scene *scene, t_object *object,
		const t_json_object *data);
int					obj_release(t_object *obj);
int					objs_release(t_object *objs, size_t num);
int					parse_material(t_object *object, const t_json_object *data);

void				mesh_face_free(int **faces, size_t size);
int					mesh_fail(void *triangles, int **faces, size_t len,
		int i);
int					mesh_calc_coord(t_clfloat3 *point, t_object *object,
		void *triangles, float scale);
int					mesh_create_triangle(t_scene *scene, void *triangles,
		int **faces, size_t *len);
int					multiple_mesh(t_scene *scene, size_t *len);
int					mesh_parse(t_scene *scene, t_object *object,
		const t_json_object *data);
int					parse_noise(const t_json_object *data, t_noise *noise);

/*
** OBJECT INITIALIZATION FUNCTIONS:
*/
int					sphere_init(t_object *object, const t_json_object *data);
int					plane_init(t_object *object, const t_json_object *data);
int					cone_init(t_object *object, const t_json_object *data);
int					cylinder_init(t_object *object, const t_json_object *data);
int					disk_init(t_object *object, const t_json_object *data);
int					triangle_init(t_object *object, const t_json_object *data);
int					cube_init(t_object *object, const t_json_object *data);
int					pyramid_init(t_object *object, const t_json_object *data);
int					paraboloid_init(t_object *object,
		const t_json_object *data);

#endif
