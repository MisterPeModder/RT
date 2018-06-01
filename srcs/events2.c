/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:44:23 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/31 20:00:00 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include "rt.h"

static void			update_keys(t_rt *c)
{
	unsigned int	i;

	i = 0;
	while (i < MAX_KEYS)
	{
		if (c->mvs.keys[i].set)
		{
			timer_end(&c->mvs.keys[i].time);
			on_key_repeat(c->mvs.keys[i].code, &c->mvs.keys[i].time, c);
			timer_start(&c->mvs.keys[i].time);
		}
		++i;
	}
}

int					on_tick(void *c)
{
	t_rt			*core;
	t_timer			timer;

	core = (t_rt *)c;
	timer_start(&timer);
	update_keys(core);
	if (core->should_update)
	{
		timer_start(&timer);
		if (render_frame(core) != CL_SUCCESS)
			ft_putendl_fd("\x1b[93mWARNING\x1b[0m: failed to render frame !!",
					STDERR_FILENO);
		else
			mlx_put_image_to_window(core->mlx.mlx_ptr, core->mlx.win_ptr,
					core->frame->mlx_img, 0, 0);
		core->should_update = 0;
		timer_end(&timer);
		timer_display(&timer, "frame time: ");
	}
	return (0);
}
