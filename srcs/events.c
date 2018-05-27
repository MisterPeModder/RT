/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:19:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 14:24:09 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "rt.h"

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

int					on_key_released(int key, void *core)
{
	if (key == ESC_KEY)
		return (exit_rt(core));
	return (0);
}

int					on_window_closing(void *core)
{
	return (exit_rt(core));
}
