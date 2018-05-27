/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:19:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 19:52:54 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "rt.h"
#include "move.h"

static int			exit_rt(t_rt *core)
{
	if (core)
	{
		scene_release(&core->scene);
		img_release(&core->mlx, &core->frame);
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

	core = (t_rt *)c;
	if (core->should_update)
	{
		render_frame(&core->scene, core->frame);
		mlx_put_image_to_window(core->mlx.mlx_ptr, core->mlx.win_ptr,
				core->frame->mlx_img, 0, 0);
		core->should_update = 0;
	}
	return (0);
}
