/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 17:44:23 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/23 16:38:53 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_events.h>
#include <libft_base/io.h>
#include <libft_base/memory.h>
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

void				on_tick(t_rt *core)
{
	cl_int			ret;
	t_timer			timer;

	timer_start(&timer);
	update_keys(core);
	if (core->state_flags & SF_SHOULD_UPDATE)
	{
		--core->sample_count;
		if ((ret = render_frame(core, &timer)) != CL_SUCCESS)
		{
			ft_putendl_fd("\x1b[93mWARNING\x1b[0m: failed to render frame !!",
					STDERR_FILENO);
			ft_putstr_fd("OpenCL error code: ", STDERR_FILENO);
			ft_putnbr_fd(ret, STDERR_FILENO);
			core->sample_count = 0;
		}
		if (core->sample_count == 0)
			core->state_flags &= ~SF_SHOULD_UPDATE;
	}
}

static void			on_mouse_wheel(SDL_MouseWheelEvent *e, t_rt *core)
{
	if (e->y != 0)
		core->mvs.move_speed += 0.1f * (float)e->y;
	if (core->mvs.move_speed < 0.f)
		core->mvs.move_speed = 0.f;
	else if (core->mvs.move_speed > 42.f)
		core->mvs.move_speed = 42.f;
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
	else if (e->type == SDL_MOUSEWHEEL)
		on_mouse_wheel(&e->wheel, core);
}

void				event_loop(t_rt *core)
{
	SDL_Event		event;

	while (1)
	{
		while (SDL_PollEvent(&event))
			handle_event(&event, core);
		on_tick(core);
	}
	on_window_closing(core);
}
