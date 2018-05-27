/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 14:23:43 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <unistd.h>
#include "rt.h"
#include "image.h"
#include "mlx_defs.h"

int					main(int ac, char **av)
{
	t_rt			core;

	if (ac != 2)
	{
		ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!mlxctx_init(&core, IMG_W, IMG_H))
		return (EXIT_FAILURE);
	if (!(core.frame = img_make(&core.mlx, IMG_W, IMG_H)) ||
			!scene_parse(&core.scene, av[1]))
	{
		img_release(&core.mlx, &core.frame);
		return (EXIT_FAILURE);
	}
	render_frame(&core.scene, core.frame);
	scene_release(&core.scene);
	mlx_put_image_to_window(core.mlx.mlx_ptr, core.mlx.win_ptr,
			core.frame->mlx_img, 0, 0);
	mlx_loop(core.mlx.mlx_ptr);
	return (EXIT_SUCCESS);
}
