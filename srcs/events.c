/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:19:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 13:33:08 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx_defs.h"
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

int					on_tick(void *c)
{
	t_rt			*core;
	t_timer			timer;

	core = (t_rt *)c;
	if (core->should_update)
	{
		timer_start(&timer);
		render_frame(core);
		mlx_put_image_to_window(core->mlx.mlx_ptr, core->mlx.win_ptr,
				core->frame->mlx_img, 0, 0);
		core->should_update = 0;
		timer_end(&timer);
		timer_display(&timer, "frame time: ");
	}
	return (0);
}
