/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 17:22:53 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/13 11:57:16 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "rtv1.h"

void				img_mlx_output(t_img *img)
{
	void			*mlx;
	void			*win;
	unsigned int	x;
	unsigned int	y;

	mlx = mlx_init();
	win = mlx_new_window(mlx, (int)img->w, (int)img->h, "rtv1");
	mlx_hook(win, X11_DESTROYNOTIFY, X11_STRUCTURENOTIFYMASK, &exit_rtv1, img);
	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			mlx_pixel_put(mlx, win, (int)x, (int)y, 0 +
					((int)img->data[x][y][0] << 16) +
					((int)img->data[x][y][1] << 8) +
					((int)img->data[x][y][2]));
			++x;
		}
		++y;
	}
	mlx_loop(mlx);
}
