/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 18:56:11 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/05 19:59:41 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void				event_loop(t_rt *core)
{
	SDL_Event		event;

	while (1) {
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				break ;
			if (event.type == SDL_KEYDOWN)
				on_key_pressed(event.key.keysym.sym, core);
			if (event.type == SDL_KEYUP)
				on_key_released(event.key.keysym.sym, core);
			on_tick(core);
		}
		SDL_Delay(10);
	}
	on_window_closing(core);
}
