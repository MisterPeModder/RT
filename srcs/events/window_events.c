/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 01:14:37 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/25 17:08:33 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <SDL_events.h>
#include <libft_base/io.h>
#include "rt.h"

void				on_window_event(void *event, t_rt *core)
{
	int				w;
	int				h;

	if (((SDL_WindowEvent *)event)->event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		SDL_GetWindowSize(core->sdl.win, &w, &h);
		core->sdl.w = (unsigned int)w;
		core->sdl.h = (unsigned int)h;
		SDL_FreeSurface(core->frame);
		if (!(core->frame = img_make(core->sdl.w, core->sdl.h)))
		{
			ft_putendl_fd("could not create frame buffer", STDERR_FILENO);
			on_window_closing(core);
		}
		core->sdl.screen = SDL_GetWindowSurface(core->sdl.win);
		core->state_flags |= SF_SHOULD_UPDATE;
	}
}
