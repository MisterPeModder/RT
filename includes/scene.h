/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 14:08:44 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/04 01:29:06 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include <libft_containers/array_list.h>
# include "objects.h"
# include "ocl_common_structs.h"
# include "filters.h"

/*
** t_scene: A structure that stores all the information about the current scene.
**
** -cam: the camera structure (see above)
** -objs: an array objects.
** -lights: an array of vectors containing the lights' positions
** -objs_num: the number of object stored
** -lights_num: the number of lights stored
** -bg_color: the background color
*/
typedef struct		s_scene
{
	t_cam			cam;
	t_object		*objs;
	t_light			*lights;
	t_mesh_triangle	*mesh_triangle;
	size_t			triangle_total_num;
	size_t			num_vertex;
	t_cluint		objs_num;
	t_cluint		lights_num;
	cl_float3		bg_color;
	t_clint			depth;
	t_filter		filter;
}					t_scene;

/*
** scene_parse: Parses the scene JSON file.
**
** -scene: the scene object
** -path: the file path
**
** returns: 1 if successful, 0 if not.
*/
int					scene_parse(t_scene *scene, const char *path);
int					scene_lights(t_scene *scene, const t_json_array *data);
void				scene_release(t_scene *scene);
void				scene_has_neg_objects(t_scene *scene, int *state);
void				mesh_face_free(int **faces, size_t size);
int					mesh_fail(t_arrlst *triangles, int **faces, size_t len,
		int i);
int					calc_coord(t_clfloat3 *point, t_object *object,
		t_arrlst *triangles);
int					create_triangle(t_scene *scene, t_arrlst *triangles,
		int **faces, size_t *len);
int					multiple_mesh(t_scene *scene, size_t *len);
void				fill_mesh_triangle(t_scene *scene, t_arrlst *triangles,
		int **faces, size_t i[3]);
int					mesh_parse(t_scene *scene, t_object *object,
		const t_json_object *data);

#endif
