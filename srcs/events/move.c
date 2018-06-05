/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 18:16:00 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/05 19:27:22 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "sdl_defs.h"

void				move_cam(t_rt *core, int key, t_timer *time)
{
	cl_float3		move_vec;
	float			increment;

	increment = core->mvs.move_speed * timer_span(time);
	if (key == SDLK_w)
		vec3cl_fill(&move_vec, 0, 0, -increment);
	else if (key == SDLK_s)
		vec3cl_fill(&move_vec, 0, 0, increment);
	else if (key == SDLK_a)
		vec3cl_fill(&move_vec, -increment, 0, 0);
	else if (key == SDLK_d)
		vec3cl_fill(&move_vec, increment, 0, 0);
	else if (key == SDLK_LSHIFT)
		vec3cl_fill(&move_vec, 0, -increment, 0);
	else
		vec3cl_fill(&move_vec, 0, increment, 0);
	rotate_x(&move_vec, core->scene.cam.angle.x);
	rotate_y(&move_vec, core->scene.cam.angle.y);
	rotate_z(&move_vec, core->scene.cam.angle.z);
	vec3cl_add(&core->scene.cam.pos, &move_vec, &core->scene.cam.pos);
	core->should_update = 1;
}

void				rotate_cam(t_rt *core, int key, t_timer *time)
{
	cl_float3		*angle;
	float			increment;

	increment = core->mvs.rotate_speed * (float)timer_span(time);
	angle = &core->scene.cam.angle;
	if (key == SDLK_UP)
		angle->x = fmod(angle->x + increment, M_PI * 2);
	else if (key == SDLK_DOWN)
		angle->x = fmod(angle->x - increment, M_PI * 2);
	else if (key == SDLK_LEFT)
		angle->y = fmod(angle->y + increment, M_PI * 2);
	else if (key == SDLK_RIGHT)
		angle->y = fmod(angle->y - increment, M_PI * 2);
	else if (key == SDLK_PAGEUP)
		angle->z = fmod(angle->z + increment, M_PI * 2);
	else
		angle->z = fmod(angle->z - increment, M_PI * 2);
	core->should_update = 1;
}
