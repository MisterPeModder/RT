/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:22:53 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/22 08:08:28 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include <libft_base/io.h>
#include "rt.h"

static void			mvs_init(t_mv_state *mvs)
{
	unsigned int	i;

	i = 0;
	while (i < MAX_KEYS)
		mvs->keys[i++].set = 0;
	mvs->move_speed = 6.0f;
	mvs->rotate_speed = 1.5f;
}

static int			sdl_win_init(t_sdl_ctx *sdl, unsigned int w, unsigned int h)
{
	SDL_DisplayMode	display;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER) < 0)
	{
		ft_putstr("Failed to initialize SDL: ");
		ft_putendl(SDL_GetError());
		return (0);
	}
	if (!(sdl->win = SDL_CreateWindow("RT",
					SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					(int)w, (int)h, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE)))
	{
		ft_putstr("Failed to open window: ");
		ft_putendl(SDL_GetError());
		return (0);
	}
	if (!SDL_GetCurrentDisplayMode(0, &display))
		SDL_SetWindowMaximumSize(sdl->win, display.w, display.h);
	SDL_SetWindowMinimumSize(sdl->win, MIN_IMG_W, MIN_IMG_H);
	sdl->screen = SDL_GetWindowSurface(sdl->win);
	sdl->show_ui = 1;
	return (1);
}

static void			controller_init(t_controller *data)
{
	data->controller = NULL;
	data->extra = NULL;
}

int					core_init(t_rt *core, unsigned int w, unsigned int h)
{
	if (!sdl_win_init(&core->sdl, w, h))
		return (0);
	core->sdl.win_width = w;
	core->sdl.win_height = h;
	mvs_init(&core->mvs);
	core->state_flags |= SF_SHOULD_UPDATE;
	core->last_time = 0;
	controller_init(&core->controller);
	return (1);
}
