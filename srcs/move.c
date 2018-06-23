/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 18:16:00 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/23 18:05:39 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "mlx_defs.h"

void				move_cam(t_rt *core, int key, t_timer *time)
{
	cl_float3		move_vec;
	float			increment;

	increment = core->mvs.move_speed * timer_span(time);
	if (key == W_KEY)
		vec3cl_fill(&move_vec, 0, 0, -increment);
	else if (key == S_KEY)
		vec3cl_fill(&move_vec, 0, 0, increment);
	else if (key == A_KEY)
		vec3cl_fill(&move_vec, -increment, 0, 0);
	else if (key == D_KEY)
		vec3cl_fill(&move_vec, increment, 0, 0);
	else if (key == SHIFT_KEY)
		vec3cl_fill(&move_vec, 0, -increment, 0);
	else
		vec3cl_fill(&move_vec, 0, increment, 0);
	rotate_x(&move_vec, core->scene.cam.angle.x);
	rotate_y(&move_vec, core->scene.cam.angle.y);
	rotate_z(&move_vec, core->scene.cam.angle.z);
	vec3cl_add(&core->scene.cam.pos, &move_vec, &core->scene.cam.pos);
	core->state_flags |= SF_SHOULD_UPDATE;
}

void				rotate_cam(t_rt *core, int key, t_timer *time)
{
	cl_float3		*angle;
	float			increment;

	increment = core->mvs.rotate_speed * (float)timer_span(time);
	angle = &core->scene.cam.angle;
	if (key == ARROW_UP_KEY)
		angle->x = fmod(angle->x + increment, M_PI * 2);
	else if (key == ARROW_DOWN_KEY)
		angle->x = fmod(angle->x - increment, M_PI * 2);
	else if (key == ARROW_LEFT_KEY)
		angle->y = fmod(angle->y + increment, M_PI * 2);
	else if (key == ARROW_RIGHT_KEY)
		angle->y = fmod(angle->y - increment, M_PI * 2);
	else if (key == PG_UP)
		angle->z = fmod(angle->z + increment, M_PI * 2);
	else
		angle->z = fmod(angle->z - increment, M_PI * 2);
	core->state_flags |= SF_SHOULD_UPDATE;
}
