/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:52:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/27 10:49:04 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft_base/io.h>
#include "rt.h"

int					print_frame(t_rt *core)
{
	SDL_Rect		img_size[2];
	int				ret;

	img_size[0] = (SDL_Rect){0, 0,
			(int)core->sdl.frame_width, (int)core->sdl.frame_height};
	img_size[1] = (SDL_Rect){0, 0,
			(int)core->sdl.win_width, (int)core->sdl.win_height};
	SDL_UnlockSurface(core->frame);
	ret = SDL_BlitScaled(core->frame, img_size, core->sdl.screen, &img_size[1]);
	ret |= SDL_UpdateWindowSurface(core->sdl.win);
	return (ret);
}

void				*ret_free(void *obj)
{
	free(obj);
	return (NULL);
}

int					rel_error(const char *msg, t_json_object **obj)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	json_release((t_json_value **)obj);
	return (0);
}

void				scene_release(t_scene *scene)
{
	free(scene->objs);
	scene->objs = NULL;
	free(scene->lights);
	scene->lights = NULL;
	if (scene->mesh_triangle != NULL)
	{
		free(scene->mesh_triangle);
		scene->mesh_triangle = NULL;
	}
}

void				scene_has_neg_objects(t_scene *scene, int *state)
{
	size_t			i;

	i = 0;
	while (i < scene->objs_num)
		if (scene->objs[i++].mat.props == MAT_NEGATIVE)
		{
			*state &= ~SF_NO_NEGATIVE;
			return ;
		}
	*state |= SF_NO_NEGATIVE;
}
