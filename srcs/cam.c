/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:36:32 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/22 19:06:08 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rt.h"

/*
** make_cam: Parses the camera properties.
**
** -cam: the camera instance.
** -data: the source JSON object.
**
** The camera requires the folliwing properties:
** "pos": an array three numbers, mandatory.
** "angle": an array of three angles, in degrees, optional.
** "fov": a number in degrees, optionnal.
**
** returns: 0 if a parse error occoured, 1 otherwise.
*/

int					make_cam(t_cam *cam, const t_json_object *data)
{
	t_json_value	*tmp;

	if (!vec3f_from_json(json_obj_get(data, "pos"), &cam->pos))
		return (0);
	if ((tmp = json_obj_get(data, "angle")))
	{
		if (!angle_from_json(tmp, &cam->angle))
			return (0);
	}
	else
		vec3f_fill(&cam->angle, 0, 0, 0);
	if ((tmp = json_obj_get(data, "fov")))
	{
		if (!float_from_json(tmp, &cam->fov) || cam->fov < 1 || cam->fov > 150)
			return (0);
	}
	else
		cam->fov = 70;
	cam->fov = to_radians(cam->fov);
	return (1);
}
