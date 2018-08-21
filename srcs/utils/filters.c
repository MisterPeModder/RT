/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 01:27:20 by jhache            #+#    #+#             */
/*   Updated: 2018/08/21 19:37:02 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "filters.h"

static void			more_filter(t_filter filter, unsigned char *frame,
		unsigned char original[3], int i)
{
	if (filter == FILTER_GREY)
	{
		frame[i] = original[0] * 0.114
			+ original[1] * 0.587 + original[2] * 0.229;
		frame[i + 1] = frame[i];
		frame[i + 2] = frame[i];
	}
	else if (filter == FILTER_NEG)
	{
		frame[i] = 255 - original[0];
		frame[i + 1] = 255 - original[1];
		frame[i + 2] = 255 - original[2];
	}
}

static void			color_filter(t_filter filter, unsigned char *frame,
		unsigned char original[3], int i)
{
	if (filter == FILTER_RED)
	{
		frame[i] = 0;
		frame[i + 1] = 0;
		frame[i + 2] = original[2];
	}
	else if (filter == FILTER_GREEN)
	{
		frame[i] = 0;
		frame[i + 1] = original[1];
		frame[i + 2] = 0;
	}
	else if (filter == FILTER_BLUE)
	{
		frame[i] = original[0];
		frame[i + 1] = 0;
		frame[i + 2] = 0;
	}
	else
		more_filter(filter, frame, original, i);
}

static void			choose_filter(t_rt *core, unsigned char *frame,
		unsigned char original[3], unsigned int tmp)
{
	int				i;

	i = 0;
	while (i < core->frame->w * core->frame->h * 4)
	{
		original[0] = (unsigned int)core->sample_sum[i] / tmp;
		original[1] = (unsigned int)core->sample_sum[i + 1] / tmp;
		original[2] = (unsigned int)core->sample_sum[i + 2] / tmp;
		if (core->scene.filter == FILTER_NONE)
		{
			frame[i] = original[0];
			frame[i + 1] = original[1];
			frame[i + 2] = original[2];
		}
		else if (core->scene.filter == FILTER_BLACK_WHITE)
		{
			frame[i] = (0.2126 * original[2] + 0.7152 * original[1]
					+ 0.0722 * original[0] > 100) ? 255 : 0;
			frame[i + 1] = frame[i];
			frame[i + 2] = frame[i];
		}
		else
			color_filter(core->scene.filter, frame, original, i);
		i += 4;
	}
}

void				apply_filter(t_rt *core)
{
	int				i;
	unsigned char	*frame;
	unsigned char	original[3];
	unsigned int	tmp;

	i = 0;
	frame = (unsigned char *)core->frame->pixels;
	tmp = core->sample_nb - core->sample_count;
	choose_filter(core, frame, original, tmp);
}
