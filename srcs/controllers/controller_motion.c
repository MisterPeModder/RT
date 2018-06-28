/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_motion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 19:01:38 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/28 16:27:40 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_events.h>
#include "rt.h"

static int			get_key_from_axis(Uint8 axis, Sint16 value, int *key)
{
	if (value == 0)
		return (0);
	if (axis == SDL_CONTROLLER_AXIS_LEFTX)
		*key = value < 0 ? SDLK_a : SDLK_d;
	else if (axis == SDL_CONTROLLER_AXIS_LEFTY)
		*key = value < 0 ? SDLK_w : SDLK_s;
	else if (axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
		*key = SDLK_LEFT;
	else if (axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
		*key = SDLK_RIGHT;
	else
		return (0);
	return (1);
}

inline static void	axis_key_release(int key1, int key2, t_rt *core)
{
	on_key_released(key1, core);
	on_key_released(key2, core);
}

void				on_controller_axis_motion(void *event, t_rt *core)
{
	SDL_ControllerAxisEvent		*e;
	int							key;

	e = (SDL_ControllerAxisEvent *)event;
	if (get_key_from_axis(e->axis, e->value, &key))
		on_key_pressed(key, core);
	else
	{
		if (e->axis == SDL_CONTROLLER_AXIS_LEFTX)
			axis_key_release(SDLK_a, SDLK_d, core);
		else if (e->axis == SDL_CONTROLLER_AXIS_LEFTY)
			axis_key_release(SDLK_w, SDLK_s, core);
		else if (e->axis == SDL_CONTROLLER_AXIS_TRIGGERLEFT)
			on_key_released(SDLK_LEFT, core);
		else if (e->axis == SDL_CONTROLLER_AXIS_TRIGGERRIGHT)
			on_key_released(SDLK_RIGHT, core);
	}
}
