/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:19:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/13 14:29:50 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx_defs.h"
#include "rtv1.h"

static int			exit_rtv1(t_img *img)
{
	if (img)
		img_release(&img);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int					on_key_released(int key, void *img)
{
	if (key == ESC_KEY)
		return (exit_rtv1(img));
	return (0);
}

int					on_window_closing(void *img)
{
	return (exit_rtv1(img));
}
