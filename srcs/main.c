/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/28 21:12:54 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <unistd.h>
#include "rt.h"
#include "image.h"
#include "mlx_defs.h"
#include "ocl_data.h"

void				compute_a_frame(t_rt *core);
cl_mem				ocl_set_kernel_arg(t_rt *core);
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
	if (ocl_init(&core->ocl) < 0)
	{
		img_release(&core->mlx, &core->frame);
		scene_release(&core->scene);
		return (0);
	}
	core.should_update = 1;
//	render_frame(&core.scene, core.frame);
//	compute_a_frame(&core);
	mlx_loop(core.mlx.mlx_ptr);
	return (EXIT_SUCCESS);
}
