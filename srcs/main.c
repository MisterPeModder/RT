/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/23 17:57:27 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <unistd.h>
#include "rt.h"
#include "image.h"
#include "mlx_defs.h"
#include "ocl_data.h"

int					main(int ac, char **av)
{
	t_rt			core;

	if (ac != 2)
	{
		ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
		return (EXIT_FAILURE);
	}
	if (!core_init(&core, IMG_W, IMG_H))
		return (EXIT_FAILURE);
	if (!(core.frame = img_make(&core.mlx, IMG_W, IMG_H)) ||
			!scene_parse(&core.scene, av[1]))
	{
		img_release(&core.mlx, &core.frame);
		return (EXIT_FAILURE);
	}
	scene_has_neg_objects(&core.scene, &core.state_flags);
	if (ocl_init(&core.ocl, &core) != CL_SUCCESS)
	{
		img_release(&core.mlx, &core.frame);
		scene_release(&core.scene);
		return (0);
	}
	mlx_loop(core.mlx.mlx_ptr);
	return (EXIT_SUCCESS);
}
