/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:22:53 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/23 18:03:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			mvs_init(t_mv_state *mvs)
{
	unsigned int	i;

	i = 0;
	while (i < MAX_KEYS)
		mvs->keys[i++].set = 0;
	mvs->move_speed = 6.0f;
	mvs->rotate_speed = 1.5f;
}

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
	mlx_hook(core->mlx.win_ptr, KEYRELEASE, KEYRELEASEMASK, &on_key_released,
			core);
	mlx_loop_hook(core->mlx.mlx_ptr, &on_tick, core);
	mvs_init(&core->mvs);
	core->state_flags |= SF_SHOULD_UPDATE;
	core->last_time = 0;
	return (1);
}
