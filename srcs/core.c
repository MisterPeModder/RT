/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:22:53 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 19:33:25 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					core_init(t_rt *core, unsigned int w, unsigned int h)
{
	if (!(core->mlx.mlx_ptr = mlx_init()))
		return (0);
	if (!(core->mlx.win_ptr = mlx_new_window(core->mlx.mlx_ptr, (int)w, (int)h,
					"rt")))
		return (0);
	core->mlx.win_width = w;
	core->mlx.win_height = h;
	mlx_hook(core->mlx.win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK,
			&on_window_closing, core);
	mlx_hook(core->mlx.win_ptr, KEYPRESS, KEYPRESSMASK, &on_key_pressed, core);
	mlx_loop_hook(core->mlx.mlx_ptr, &on_tick, core);
	core->should_update = 1;
	return (1);
}
