/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:19:36 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/22 19:07:19 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "mlx_defs.h"
#include "rt.h"

static int			exit_rt(t_img *img)
{
	if (img)
		img_release(&img);
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

int					on_key_released(int key, void *img)
{
	if (key == ESC_KEY)
		return (exit_rt(img));
	return (0);
}

int					on_window_closing(void *img)
{
	return (exit_rt(img));
}
