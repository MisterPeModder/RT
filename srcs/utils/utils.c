/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:52:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/03 15:03:44 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft_base/io.h>
#include "rt.h"

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

void				average_sample(t_rt *core)
{
	int				i;
	unsigned char	*frame;

	i = 0;
	frame = (unsigned char *)core->frame->pixels;
	if (core->sample_nb - core->sample_count == 1)
	{
		while (i < core->frame->w * core->frame->h * 4)
		{
			core->sample_sum[i] = frame[i];
			++i;
		}
	}
	else
	{
		while (i < core->frame->w * core->frame->h * 4)
		{
			core->sample_sum[i] += frame[i];
			frame[i] = core->sample_sum[i] /
				(int)(core->sample_nb - core->sample_count);
			++i;
		}
	}
}

static void			apply_filter2(t_rt *core, unsigned char *frame, int i)
{
	if (core->scene.filter == 1)
	{
		frame[i] = 0;
		frame[i + 1] = 0;
	}
	if (core->scene.filter == 2)
	{
		frame[i] = 0;
		frame[i + 2] = 0;
	}
	if (core->scene.filter == 3)
	{
		frame[i + 1] = 0;
		frame[i + 2] = 0;
	}
	if (core->scene.filter == 4)
	{
		frame[i] = frame[i] * 0.114 + frame[i + 1] * 0.587 + frame[i + 2]
			* 0.229;
		frame[i + 1] = frame[i];
		frame[i + 2] = frame[i];
	}
}

void				apply_filter(t_rt *core)
{
	int				i;
	unsigned char	*frame;
	int				brightness;

	i = 0;
	frame = (unsigned char *)core->frame->pixels;
	if (core->scene.filter == -1)
		return ;
	while (i < core->frame->w * core->frame->h * 4)
	{
		apply_filter2(core, frame, i);
		if (core->scene.filter == 5)
		{
			brightness = 0.2126 * frame[i + 2] + 0.7152 * frame[i + 1] +
				0.0722 * frame[i];
			if (brightness > 100)
				brightness = 255;
			else
					brightness = 0;
			frame[i] = brightness;
			frame[i + 1] = brightness;
			frame[i + 2] = brightness;
		}
		i += 4;
	}
}
