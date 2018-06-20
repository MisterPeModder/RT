/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_event.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:55:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/08 17:44:01 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_events.h>
#include <libft_base/io.h>
#include "rt.h"

void					on_controller_button_pressed(void *event, t_rt *core)
{
	SDL_ControllerButtonEvent	*e;

	e = (SDL_ControllerButtonEvent *)event;
	ft_putstr("controller button down: ");
	ft_putendl(SDL_GameControllerGetStringForButton(e->button));
	if (e->button == SDL_CONTROLLER_BUTTON_GUIDE)
		on_window_closing(core);
}

void					on_controller_button_released(void *event, t_rt *core)
{
	(void)event;
	(void)core;
}

void					on_controller_connect(Sint32 id, t_rt *core)
{
	ft_putstr("[connected] controller: ");
	ft_putnbr((int)id);
	ft_putchar('\n');
	controller_update(&core->controller);
}

void					on_controller_disconnect(Sint32 id, t_rt *core)
{
	ft_putstr("[disconnected] controller: ");
	ft_putnbr((int)id);
	ft_putchar('\n');
	SDL_GameControllerClose(core->controller.controller);
	core->controller.controller = NULL;
	controller_update(&core->controller);
}
