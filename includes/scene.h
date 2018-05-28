/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 14:08:44 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/28 21:43:16 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "objects.h"
# include "ocl_common_structs.h"

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
	size_t			objs_num;
	size_t			lights_num;
	t_vec3f			bg_color;
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

#endif
