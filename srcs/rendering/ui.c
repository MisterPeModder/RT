/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 15:29:03 by jhache            #+#    #+#             */
/*   Updated: 2018/08/11 16:25:32 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_ttf.h>
#include <libft_base/io.h>
#include "rt.h"

static void			wipe_surface(SDL_Surface *s)
{
	SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_NONE);
	SDL_FillRect(s, NULL, SDL_MapRGBA(s->format, 0, 0, 0, 0));
	SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_BLEND);
}

static void			draw_text_box(t_rt *core, const char *str[3], int x, int y)
{
	SDL_Surface		*text;
	SDL_Rect		dims;
	int				i;

	i = 0;
	while (i < 3)
	{
		text = TTF_RenderText_Blended(core->sdl.font, str[i],
				(SDL_Color){255, 255, 255, 255});
		++i;
		dims = (SDL_Rect){x, y,
			text->w + TXT_BOX_PADDING * 2, text->h + TXT_BOX_PADDING * 2};
		SDL_FillRect(core->sdl.ui, &dims,
				SDL_MapRGBA(core->sdl.ui->format, 0, 0, 0, 100));
		dims = (SDL_Rect){x + TXT_BOX_PADDING, y + TXT_BOX_PADDING,
			(int)core->sdl.win_width - TXT_BOX_PADDING,
			(int)core->sdl.win_height - TXT_BOX_PADDING};
		SDL_BlitSurface(text, NULL, core->sdl.ui, &dims);
		SDL_FreeSurface(text);
		y += text->h + TXT_BOX_PADDING;
	}
}

void				render_ui(t_rt *core, t_timer *t)
{
	char			*str[3];

	SDL_FreeSurface(core->sdl.ui);
	core->sdl.ui = NULL;
	if (!core->sdl.show_ui)
		return ;
	if (!(core->sdl.ui = img_make(core->sdl.win_width,
					core->sdl.win_height)))
	{
		ft_putendl_fd("could not create UI buffer", STDERR_FILENO);
	}
	wipe_surface(core->sdl.ui);
	str[0] = display_fps(core, t, 0);
	str[1] = display_sample(core);
	str[2] = display_depth(core);
	draw_text_box(core, (const char**)str, 0, 0);
	free(str[0]);
	free(str[1]);
	free(str[2]);
}
