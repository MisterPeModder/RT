/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 22:11:03 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <unistd.h>
#include "rt.h"
#include "image.h"
#include "mlx_defs.h"
#include "ocl_data.h"

static int			init_core(t_rt *core, char *scene_file)
{
	if (!mlxctx_init(core, IMG_W, IMG_H))
		return (0);
	if (!(core->frame = img_make(&core->mlx, IMG_W, IMG_H)) ||
			!scene_parse(&core->scene, scene_file))
	{
		img_release(&core->mlx, &core->frame);
		return (0);
	}
	if (ocl_init(&core->ocl) < 0)
	{
		img_release(&core->mlx, &core->frame);
		scene_release(&core->scene);
		return (0);
	}
	return (1);
}

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
	if (init_core(&core, av[1]) == 0)
		return (EXIT_FAILURE);
//	render_frame(&core.scene, core.frame);
	compute_a_frame(&core);
	mlx_put_image_to_window(core.mlx.mlx_ptr, core.mlx.win_ptr,
			core.frame->mlx_img, 0, 0);
	mlx_loop(core.mlx.mlx_ptr);
	return (EXIT_SUCCESS);
}
