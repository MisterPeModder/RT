/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 16:13:26 by jhache            #+#    #+#             */
/*   Updated: 2018/08/11 16:36:32 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <libft_base/stringft.h>
#include "rt.h"

char				*display_fps(t_rt *core, t_timer *t, int last)
{
	char			*str;
	char			*fps;

	timer_end(t);
	str = ft_memalloc(sizeof(char) * 256);
	if (!last)
		core->last_time = timer_span(t);
	if ((fps = ft_dtoa((core->last_time ? 1 / core->last_time : 0), 2)))
	{
		ft_strncpy(str, fps, 256);
		ft_strlcat(str, "FPS - ", 256);
		free(fps);
	}
	if ((fps = ft_dtoa(core->last_time, 2)))
	{
		ft_strlcat(str, fps, 256);
		ft_strlcat(str, "s", 256);
		free(fps);
	}
	return (str);
}

char				*display_depth(t_rt *core)
{
	char			*str;
	char			*depth_nb;

	depth_nb = ft_itoa(core->scene.depth);
	str = ft_memalloc(sizeof(char) * 256);
	ft_strlcat(str, "Depth : ", 256);
	ft_strlcat(str, depth_nb, 256);
	free(depth_nb);
	return (str);
}

char				*display_sample(t_rt *core)
{
	char			*str;
	char			*sample_nb;
	char			*sample_count;
	int				tmp;

	tmp = (int)(core->sample_nb - core->sample_count);
	sample_nb = ft_itoa((int)core->sample_nb);
	sample_count = ft_itoa(tmp);
	str = ft_memalloc(sizeof(char) * 256);
	ft_strlcat(str, "Sample : ", 256);
	ft_strlcat(str, sample_count, 256);
	ft_strlcat(str, " / ", 256);
	ft_strlcat(str, sample_nb, 256);
	free(sample_nb);
	free(sample_count);
	return (str);
}
