/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_events.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 01:14:37 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/31 02:03:09 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <SDL_ttf.h>
#include <SDL_events.h>
#include <libft_base/io.h>
#include <libft_base/memory.h>
#include "rt.h"

static int			remake_surfaces(t_rt *core)
{
	free(core->sample_sum);
	SDL_FreeSurface(core->frame);
	SDL_FreeSurface(core->sdl.ui);
	TTF_CloseFont(core->sdl.font);
	if (!(core->frame = img_make(core->sdl.frame_width,
					core->sdl.frame_height)))
		ft_putendl_fd("could not create frame buffer", STDERR_FILENO);
	else if (!(core->sdl.ui = img_make(core->sdl.win_width,
					core->sdl.win_height)))
		ft_putendl_fd("could not create UI buffer", STDERR_FILENO);
	else if (!(core->sdl.font = TTF_OpenFont(core->sdl.font_name,
					(int)core->sdl.win_width / 100 + 8)))
	{
		ft_putstr("Failed to load font: ");
		ft_putendl(TTF_GetError());
		return (0);
	}
	else if ((core->sample_sum = (int *)ft_memalloc(sizeof(int)
					* core->sdl.frame_width
					* core->sdl.frame_height * 4)) == NULL)
		ft_putendl_fd("could not create Sample buffer", STDERR_FILENO);
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
		free(core->sample_sum);
		core->sample_sum = (int *)ft_memalloc(sizeof(int)
				* core->sdl.frame_width * core->sdl.frame_height * 4);
		if (core->sample_sum == NULL)
		{
			ft_putendl("malloc error at on_window_event().");
			exit(EXIT_FAILURE);
		}
		if (!remake_surfaces(core))
			on_window_closing(core);
		core->sdl.screen = SDL_GetWindowSurface(core->sdl.win);
		core->state_flags |= SF_SHOULD_UPDATE;
		core->sample_count = core->sample_nb;
	}
}
