/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:36:32 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/07 00:39:22 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

int					make_cam(t_cam *cam, const t_json_object *data)
{
	t_json_value	*tmp;

	if (!vec3f_from_json(json_obj_get(data, "pos"), &cam->pos))
		return (0);
	if ((tmp = json_obj_get(data, "angle")))
	{
		if (!vec3f_from_json(tmp, &cam->angle))
			return (0);
		cam->angle.x = to_radians(cam->angle.x);
		cam->angle.y = to_radians(cam->angle.y);
		cam->angle.z = to_radians(cam->angle.z);
	}
	else
		vec3f_fill(&cam->angle, 0, 0, 0);
	if ((tmp = json_obj_get(data, "fov")))
	{
		if (!float_from_json(tmp, &cam->fov))
			return (0);
	}
	else
		cam->fov = 70;
	cam->fov = to_radians(cam->fov);
	return (1);
}
