/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:19:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/23 05:14:03 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_ttf.h>
#include "rt.h"
#include "move.h"

void				exit_rt(t_rt *core)
{
	if (core)
	{
		clReleaseMemObject(core->mem_objects->arg1);
		clReleaseMemObject(core->mem_objects->arg2);
		clReleaseMemObject(core->mem_objects->arg3);
		clReleaseMemObject(core->mem_objects->arg12);
		clReleaseMemObject(core->mem_objects->arg13);
		free(core->mem_objects);
		scene_release(&core->scene);
		ocl_release(&core->ocl, NULL, 0);
		SDL_DestroyWindow(core->sdl.win);
		SDL_FreeSurface(core->frame);
		SDL_GameControllerClose(core->controller.controller);
		TTF_CloseFont(core->sdl.font);
		free(core->sample_sum);
	}
	TTF_Quit();
	SDL_Quit();
	exit(EXIT_SUCCESS);
}

void				on_key_pressed(int key, t_rt *core)
{
	t_mv_state		*mvs;
	unsigned int	i;

	key_handling(key, core);
	mvs = &core->mvs;
	i = 0;
	while (i < MAX_KEYS)
		if (mvs->keys[i++].set && mvs->keys[i - 1].code == key)
			return ;
	i = 0;
	while (i < MAX_KEYS)
		if (!mvs->keys[i++].set)
		{
			mvs->keys[i - 1].code = key;
			mvs->keys[i - 1].set = 1;
			timer_start(&mvs->keys[i - 1].time);
			return ;
		}
}

void				on_key_released(int key, t_rt *core)
{
	t_mv_state		*mvs;
	unsigned int	i;

	mvs = &core->mvs;
	i = 0;
	while (i < MAX_KEYS)
	{
		if (mvs->keys[i].set && mvs->keys[i].code == key)
			mvs->keys[i].set = 0;
		++i;
	}
}

void				on_key_repeat(int key, t_timer *time, t_rt *core)
{
	if (key == SDLK_w || key == SDLK_a || key == SDLK_s || key == SDLK_d
			|| key == SDLK_LSHIFT || key == SDLK_SPACE)
		move_cam(core, key, time);
	else if (key == SDLK_UP || key == SDLK_LEFT
			|| key == SDLK_DOWN || key == SDLK_RIGHT
			|| key == SDLK_PAGEUP || key == SDLK_PAGEDOWN)
		rotate_cam(core, key, time);
}

void				on_window_closing(t_rt *core)
{
	return (exit_rt(core));
}
