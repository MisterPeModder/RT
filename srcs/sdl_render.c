/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 11:45:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/03 06:56:56 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_ttf.h>
#include <libft_base/io.h>
#include <libft_base/memory.h>
#include <libft_base/stringft.h>
#include "rt.h"

static void			wipe_surface(SDL_Surface *s)
{
	SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_NONE);
	SDL_FillRect(s, NULL, SDL_MapRGBA(s->format, 0, 0, 0, 0));
	SDL_SetSurfaceBlendMode(s, SDL_BLENDMODE_BLEND);
}

void				draw_text_box(t_rt *core, const char *str, int x, int y)
{
	SDL_Surface		*text;
	SDL_Rect		dims;

	text = TTF_RenderText_Blended(core->sdl.font, str,
			(SDL_Color){255, 255, 255, 255});
	dims = (SDL_Rect){x, y,
		text->w + TXT_BOX_PADDING * 2, text->h + TXT_BOX_PADDING * 2};
	SDL_FillRect(core->sdl.ui, &dims,
			SDL_MapRGBA(core->sdl.ui->format, 0, 0, 0, 100));
	dims = (SDL_Rect){x + TXT_BOX_PADDING, y + TXT_BOX_PADDING,
		(int)core->sdl.win_width - TXT_BOX_PADDING,
		(int)core->sdl.win_height - TXT_BOX_PADDING};
	SDL_BlitSurface(text, NULL, core->sdl.ui, &dims);
	(void)str;
	SDL_FreeSurface(text);
}

static void			display_fps(t_rt *core, t_timer *t, int last)
{
	char			buff[256];
	char			*fps;

	timer_end(t);
	ft_bzero(buff, 256);
	if (!last)
		core->last_time = timer_span(t);
	if ((fps = ft_dtoa((core->last_time ? 1 / core->last_time : 0), 2)))
	{
		ft_strncpy(buff, fps, 256);
		ft_strlcat(buff, "FPS - ", 256);
		free(fps);
	}
	if ((fps = ft_dtoa(core->last_time, 2)))
	{
		ft_strlcat(buff, fps, 256);
		ft_strlcat(buff, "s", 256);
		free(fps);
	}
	draw_text_box(core, buff, 0, 0);
}

static void			render_ui(t_rt *core, t_timer *t)
{
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
	display_fps(core, t, 0);
}

int					print_frame(t_rt *core, t_timer *t)
{
	SDL_Rect		img_size[2];
	int				ret;

	img_size[0] = (SDL_Rect){0, 0,
		(int)core->sdl.frame_width, (int)core->sdl.frame_height};
	img_size[1] = (SDL_Rect){0, 0,
		(int)core->sdl.win_width, (int)core->sdl.win_height};
	average_sample(core);
	SDL_UnlockSurface(core->frame);
	render_ui(core, t);
	(void)t, (void)render_ui, (void)display_fps;
	if ((ret = SDL_BlitScaled(core->frame, img_size,
					core->sdl.screen, &img_size[1])))
		return (ret);
	if (core->sdl.show_ui && (ret = SDL_BlitSurface(core->sdl.ui, NULL,
					core->sdl.screen, &img_size[1])))
		return (ret);
	return (SDL_UpdateWindowSurface(core->sdl.win));
}
