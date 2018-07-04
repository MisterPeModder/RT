/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 01:27:20 by jhache            #+#    #+#             */
/*   Updated: 2018/07/04 01:45:53 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "filters.h"

static void			apply_filter2(t_rt *core, unsigned char *frame, int i)
{
	if (core->scene.filter == FILTER_RED)
	{
		frame[i] = 0;
		frame[i + 1] = 0;
	}
	if (core->scene.filter == FILTER_GREEN)
	{
		frame[i] = 0;
		frame[i + 2] = 0;
	}
	if (core->scene.filter == FILTER_BLUE)
	{
		frame[i + 1] = 0;
		frame[i + 2] = 0;
	}
	if (core->scene.filter == FILTER_GREY)
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
	if (core->scene.filter == FILTER_NONE)
		return ;
	while (i < core->frame->w * core->frame->h * 4)
	{
		apply_filter2(core, frame, i);
		if (core->scene.filter == FILTER_BLACK_WHITE)
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
