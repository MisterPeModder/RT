/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 11:45:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/11 15:49:53 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					print_frame(t_rt *core, t_timer *t)
{
	SDL_Rect		img_size[2];
	int				ret;

	img_size[0] = (SDL_Rect){0, 0,
		(int)core->sdl.frame_width, (int)core->sdl.frame_height};
	img_size[1] = (SDL_Rect){0, 0,
		(int)core->sdl.win_width, (int)core->sdl.win_height};
	apply_filter(core);
	SDL_UnlockSurface(core->frame);
	if (t != NULL)
		render_ui(core, t);
	if ((ret = SDL_BlitScaled(core->frame, img_size,
					core->sdl.screen, &img_size[1])))
		return (ret);
	if (core->sdl.show_ui && (ret = SDL_BlitSurface(core->sdl.ui, NULL,
					core->sdl.screen, &img_size[1])))
		return (ret);
	return (SDL_UpdateWindowSurface(core->sdl.win));
}
