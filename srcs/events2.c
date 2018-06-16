/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:44:23 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/16 11:54:46 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <libft_base/stringft.h>
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

static void			display_fps(t_rt *core, t_timer *t, int last)
{
	char			*fps;

	timer_end(t);
	if (!last)
		core->last_time = timer_span(t);
	if ((fps = ft_dtoa((core->last_time ? 1 / core->last_time : 0), 2)))
	{
		ft_putstr(fps);
		ft_putstr("fps - ");
		free(fps);
	}
	if ((fps = ft_dtoa(core->last_time, 2)))
	{
		ft_putstr(fps);
		ft_putendl("s");
		free(fps);
	}
}

int					on_tick(void *c)
{
	t_rt			*core;
	t_timer			timer;

	timer_start(&timer);
	core = (t_rt *)c;
	update_keys(core);
	if (core->should_update)
	{
		if (render_frame(core) != CL_SUCCESS)
			ft_putendl_fd("\x1b[93mWARNING\x1b[0m: failed to render frame !!",
					STDERR_FILENO);
		else
			mlx_put_image_to_window(core->mlx.mlx_ptr, core->mlx.win_ptr,
					core->frame->mlx_img, 0, 0);
		core->should_update = 0;
		display_fps(core, &timer, 0);
	}
	else
		display_fps(core, &timer, 1);
	return (0);
}
