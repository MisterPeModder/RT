/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 14:08:44 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/14 09:14:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "mesh.h"
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
	t_mesh_triangle	*mesh_triangles;
	size_t			objs_num;
	size_t			lights_num;
	size_t			triangles_num;
	size_t			vertices_num;
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

#endif
