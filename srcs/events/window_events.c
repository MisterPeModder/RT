/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 01:14:37 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/29 22:41:04 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <SDL_ttf.h>
#include <SDL_events.h>
#include <libft_base/io.h>
#include "rt.h"

static int			remake_surfaces(t_rt *core)
{
	SDL_FreeSurface(core->frame);
	SDL_FreeSurface(core->sdl.ui);
	if (!(core->frame = img_make(core->sdl.frame_width,
					core->sdl.frame_height)))
	{
		ft_putendl_fd("could not create frame buffer", STDERR_FILENO);
	}
	else if (!(core->sdl.ui = img_make(core->sdl.win_width,
					core->sdl.win_height)))
	{
		ft_putendl_fd("could not create UI buffer", STDERR_FILENO);
	}
	else if (!(core->sdl.font = TTF_OpenFont(
					"./assets/Arcon-Regular.otf",
					(int)core->sdl.win_width / 100 * 1 + 8)))
	{

		ft_putstr("Failed to load font: ");
		ft_putendl(TTF_GetError());
		return (0);
	}
	else
		return (1);
	SDL_SetSurfaceBlendMode(core->sdl.ui, SDL_BLENDMODE_BLEND);
	return (0);
}

void				on_window_event(void *event, t_rt *core)
{
	int				w;
	int				h;

	if (((SDL_WindowEvent *)event)->event == SDL_WINDOWEVENT_SIZE_CHANGED)
	{
		SDL_GetWindowSize(core->sdl.win, &w, &h);
		core->sdl.win_width = (unsigned int)w;
		core->sdl.win_height = (unsigned int)h;
		update_frame_size(core, &core->mem_info);
		init_kernel_args(&core->ocl, core);
		if (!remake_surfaces(core))
			on_window_closing(core);
		core->sdl.screen = SDL_GetWindowSurface(core->sdl.win);
		core->state_flags |= SF_SHOULD_UPDATE;
	}
}
