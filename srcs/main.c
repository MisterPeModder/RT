/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/28 16:13:40 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			quit_release(t_rt *core)
{
	SDL_FreeSurface(core->frame);
	scene_release(&core->scene);
	ocl_release(&core->ocl, NULL, 0);
}

int					main(int ac, char **av)
{
	t_rt			core;
	int				ret;
	char			*options_path;

	if ((ret = parse_args(ac, av, &options_path)))
		return (ret == 1 ? EXIT_FAILURE : EXIT_SUCCESS);
	if (!scene_parse(&core.scene, av[ac - 1])
			|| !options_parse(&core, options_path)
			|| !core_init(&core, core.sdl.win_width, core.sdl.win_height)
			|| ocl_init(&core.ocl) != CL_SUCCESS)
	{
		quit_release(&core);
		return (EXIT_FAILURE);
	}
	if (load_first_kernel_args(&core) != CL_SUCCESS
			|| !(core.frame = img_make(core.sdl.frame_width,
					core.sdl.frame_height)))
	{
		quit_release(&core);
		return (EXIT_FAILURE);
	}
	scene_has_neg_objects(&core.scene, &core.state_flags);
	controller_update(&core.controller);
	event_loop(&core);
	return (EXIT_SUCCESS);
}
