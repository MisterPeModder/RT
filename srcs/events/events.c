/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:19:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/06 00:42:03 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "move.h"

static int			exit_rt(t_rt *core)
{
	if (core)
	{
		scene_release(&core->scene);
		ocl_release(&core->ocl, NULL, 0);
		SDL_DestroyWindow(core->sdl.win);
		SDL_FreeSurface(core->frame);
	}
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int					on_key_pressed(int key, void *core)
{
	t_mv_state		*mvs;
	unsigned int	i;

	if (key == SDLK_ESCAPE)
		return (exit_rt(core));
	mvs = &((t_rt *)core)->mvs;
	i = 0;
	while (i < MAX_KEYS)
		if (mvs->keys[i++].set && mvs->keys[i - 1].code == key)
			return (0);
	i = 0;
	while (i < MAX_KEYS)
		if (!mvs->keys[i++].set)
		{
			mvs->keys[i - 1].code = key;
			mvs->keys[i - 1].set = 1;
			timer_start(&mvs->keys[i - 1].time);
			return (0);
		}
	return (0);
}

int					on_key_released(int key, void *core)
{
	t_mv_state		*mvs;
	unsigned int	i;

	mvs = &((t_rt *)core)->mvs;
	i = 0;
	while (i < MAX_KEYS)
	{
		if (mvs->keys[i].set && mvs->keys[i].code == key)
			mvs->keys[i].set = 0;
		++i;
	}
	return (0);
}

void				on_key_repeat(int key, t_timer *time, void *core)
{
	if (key == SDLK_w || key == SDLK_a || key == SDLK_s || key == SDLK_d ||
			key == SDLK_LSHIFT || key == SDLK_SPACE)
		move_cam(core, key, time);
	else if (key == SDLK_UP || key == SDLK_LEFT ||
			key == SDLK_DOWN || key == SDLK_RIGHT ||
			key == SDLK_PAGEUP || key == SDLK_PAGEDOWN)
		rotate_cam(core, key, time);
}

int					on_window_closing(void *core)
{
	return (exit_rt(core));
}
