/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 07:17:03 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/23 08:55:51 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_ttf.h>
#include <libft_base/io.h>
#include <libft_base/stringft.h>
#include "rt.h"

static int			options_error(const char *err)
{
	ft_putstr_fd("Error while reading options file: ", STDERR_FILENO);
	ft_putendl_fd(err, STDERR_FILENO);
	return (0);
}

static int			options_window(t_rt *core, const t_json_object *data)
{
	t_json_value	*tmp;
	int				nw;
	int				nh;
	int				fs;

	SDL_GetWindowSize(core->sdl.win, &nw, &nh);
	if ((tmp = json_obj_get(data, "width")) && !int_from_json(tmp, &nw))
		return (options_error("invalid window width property"));
	if ((tmp = json_obj_get(data, "height")) && !int_from_json(tmp, &nh))
		return (options_error("invalid window height property"));
	if (nw < MIN_IMG_W)
		return (options_error("window width is too small"));
	if (nh < MIN_IMG_H)
		return (options_error("window height is too small"));
	fs = 0;
	if ((tmp = json_obj_get(data, "fullscreen")) && !bool_from_json(tmp, &fs))
		return (options_error("\"fullscreen\" property must be a boolean"));
	SDL_SetWindowSize(core->sdl.win, nw, nh);
	core->sdl.win_width = (unsigned int)nw;
	core->sdl.win_height = (unsigned int)nh;
	if (fs)
		SDL_SetWindowFullscreen(core->sdl.win, SDL_WINDOW_FULLSCREEN_DESKTOP);
	return (1);
}

static int			options_font(t_sdl_ctx *sdl, const t_json_value *data)
{
	if (!data)
		ft_strncpy(sdl->font_name, "assets/Arcon-Regular.otf", MAX_FONT_NAME);
	else if (data->str.type != JSON_STRING)
		return (options_error("\"font\" property must be a string"));
	else
		ft_strncpy(sdl->font_name, data->str.value, MAX_FONT_NAME);
	if (TTF_Init() < 0)
	{
		ft_putstr("Failed to initialize SDL TTF: ");
		ft_putendl(TTF_GetError());
		return (0);
	}
	return (1);
}

int					options_parse(t_rt *core, const char *path)
{
	t_json_object	*obj;
	t_json_value	*tmp;

	if (!(obj = &(json_file_read(path)->obj))
			|| !options_font(&core->sdl, json_obj_get(obj, "font")))
		return (0);
	if ((tmp = json_obj_get(obj, "window")))
	{
		if (tmp->obj.type != JSON_OBJECT)
			return (options_error("\"window\" property must be an object"));
		if (!options_window(core, &tmp->obj))
			return (0);
	}
	if (!(tmp = json_obj_get(obj, "sample_nb")))
		return (rel_error("No sample number specified in the options file.",
					&obj));
	else if (tmp->n_i.type != JSON_INT || tmp->n_i.value < 1
			|| tmp->n_i.value > 20)
		return (rel_error("The number of sample must be between 1 and 20.",
					&obj));
	else
		core->sample_nb = (unsigned int)tmp->n_i.value;
	json_release((t_json_value **)&obj);
	return (1);
}
