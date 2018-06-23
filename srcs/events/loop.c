/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:44:23 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/23 20:22:50 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_events.h>
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

void				on_tick(t_rt *core)
{
	t_timer			timer;

	timer_start(&timer);
	update_keys(core);
	if (core->state_flags & SF_SHOULD_UPDATE)
	{
		if (render_frame(core) != CL_SUCCESS)
			ft_putendl_fd("\x1b[93mWARNING\x1b[0m: failed to render frame !!",
					STDERR_FILENO);
		core->state_flags &= ~SF_SHOULD_UPDATE;
		display_fps(core, &timer, 0);
	}
}

static void			handle_event(SDL_Event *e, t_rt *core)
{
	if (e->type == SDL_QUIT)
		on_window_closing(core);
	else if (e->type == SDL_KEYDOWN)
		on_key_pressed(e->key.keysym.sym, core);
	else if (e->type == SDL_KEYUP)
		on_key_released(e->key.keysym.sym, core);
	else if (e->type == SDL_WINDOWEVENT)
		on_window_event(&e->window, core);
	else if (e->type == SDL_CONTROLLERBUTTONDOWN)
		on_controller_button_pressed(&e->cbutton, core);
	else if (e->type == SDL_CONTROLLERBUTTONUP)
		on_controller_button_released(&e->cbutton, core);
	else if (e->type == SDL_CONTROLLERDEVICEADDED)
		on_controller_connect(e->cdevice.which, core);
	else if (e->type == SDL_CONTROLLERDEVICEREMOVED)
		on_controller_disconnect(e->cdevice.which, core);
	else if (e->type == SDL_CONTROLLERAXISMOTION)
		on_controller_axis_motion(&e->caxis, core);
}

void				event_loop(t_rt *core)
{
	SDL_Event		event;

	while (1)
	{
		on_tick(core);
		while (SDL_PollEvent(&event))
			handle_event(&event, core);
	}
	on_window_closing(core);
}
