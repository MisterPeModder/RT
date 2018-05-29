/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:19:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 07:20:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "rt.h"
#include "ocl_data.h"
#include "move.h"
#include "timer.h"

static int			exit_rt(t_rt *core)
{
	if (core)
	{
		scene_release(&core->scene);
		img_release(&core->mlx, &core->frame);
		ocl_release(&core->ocl, NULL, 0);
	}
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int					on_key_pressed(int key, void *core)
{
	if (key == ESC_KEY)
		return (exit_rt(core));
	else if (key == W_KEY || key == A_KEY || key == S_KEY || key == D_KEY ||
			key == SHIFT_KEY || key == SPACE_KEY)
		move_cam(core, key);
	return (0);
}

int					on_window_closing(void *core)
{
	return (exit_rt(core));
}

//WTF ??
void				compute_a_frame(t_rt *core);
cl_mem				ocl_set_kernel_arg(t_rt *core);

#include <stdio.h>

int					on_tick(void *c)
{
	t_rt			*core;
	t_timer			timer;

	core = (t_rt *)c;
	if (core->should_update)
	{
		//printf("start\n");
		timer_start(&timer);
		render_frame(core);
		//printf("wie bitte?\n");
		mlx_put_image_to_window(core->mlx.mlx_ptr, core->mlx.win_ptr,
				core->frame->mlx_img, 0, 0);
		//printf("was?\n");
		core->should_update = 0;
		timer_end(&timer);
		timer_display(&timer);
		//printf("end\n");
	}
	return (0);
}
