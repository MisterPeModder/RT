/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/20 02:56:32 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <libft_base/memory.h>

static void			quit_release(t_rt *core)
{
	SDL_FreeSurface(core->frame);
	scene_release(&core->scene);
	ocl_release(&core->ocl, NULL, 0);
}

static int			init_data(int ac, char **av, t_rt *core)
{
	int				ret;
	char			*options_path;

	if ((ret = parse_args(ac, av, &options_path)))
		return (ret == 1 ? -1 : 0);
	if (!scene_parse(&core->scene, av[ac - 1])
			|| !options_parse(core, options_path)
			|| !core_init(core, core->sdl.win_width, core->sdl.win_height)
			|| ocl_init(&core->ocl) != CL_SUCCESS)
		return (-1);
	if (load_first_kernel_args(core) != CL_SUCCESS
			|| !(core->frame = img_make(core->sdl.frame_width,
					core->sdl.frame_height))
			|| !(core->sample_sum = (int *)ft_memalloc(sizeof(int)
					* core->sdl.frame_width * core->sdl.frame_height * 4)))
		return (-1);
	return (1);
}

int					main(int ac, char **av)
{
	t_rt			core;
	int				ret;

	if ((ret = init_data(ac, av, &core)) != 1)
	{
		quit_release(&core);
		while (1)
			;
		return (ret == -1 ? EXIT_FAILURE : EXIT_SUCCESS);
	}
	core.sample_count = core.sample_nb;
	core.mem_info.used_local_mem = 0;
	scene_has_neg_objects(&core.scene, &core.state_flags);
	controller_update(&core.controller);
	event_loop(&core);
	return (EXIT_SUCCESS);
}
