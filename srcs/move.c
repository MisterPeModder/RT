/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 18:16:00 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 01:38:37 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "move.h"
#include "mlx_defs.h"

void				move_cam(t_rt *core, int key)
{
	cl_float3		move_vec;

	if (key == W_KEY)
		vec3cl_fill(&move_vec, 0, 0, -MOVE_INCREMENT);
	else if (key == S_KEY)
		vec3cl_fill(&move_vec, 0, 0, MOVE_INCREMENT);
	else if (key == A_KEY)
		vec3cl_fill(&move_vec, -MOVE_INCREMENT, 0, 0);
	else if (key == D_KEY)
		vec3cl_fill(&move_vec, MOVE_INCREMENT, 0, 0);
	else if (key == SHIFT_KEY)
		vec3cl_fill(&move_vec, 0, -MOVE_INCREMENT, 0);
	else
		vec3cl_fill(&move_vec, 0, MOVE_INCREMENT, 0);
	rotate_x(&move_vec, core->scene.cam.angle.x);
	rotate_y(&move_vec, core->scene.cam.angle.y);
	rotate_z(&move_vec, core->scene.cam.angle.z);
	vec3cl_add(&core->scene.cam.pos, &move_vec, &core->scene.cam.pos);
	core->should_update = 1;
}
