/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:56:11 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/06 01:10:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_events.h>
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
		core->should_update = 0;
		timer_end(&timer);
		timer_display(&timer, "frame time: ");
	}
	return (0);
}

void				event_loop(t_rt *core)
{
	SDL_Event		event;

	while (1)
	{
		on_tick(core);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				on_window_closing(core);
			if (event.type == SDL_KEYDOWN)
				on_key_pressed(event.key.keysym.sym, core);
			if (event.type == SDL_KEYUP)
				on_key_released(event.key.keysym.sym, core);
		}
	}
	on_window_closing(core);
}
