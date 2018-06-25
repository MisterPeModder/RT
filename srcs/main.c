/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/25 22:20:27 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			quit_release(t_rt *core)
{
	SDL_FreeSurface(core->frame);
	scene_release(&core->scene);
}

int					main(int ac, char **av)
{
	t_rt			core;
	int				ret;
	char			*options_path;

	if ((ret = parse_args(ac, av, &options_path)))
		return (ret == 1 ? EXIT_FAILURE : EXIT_SUCCESS);
	if (!core_init(&core, IMG_W, IMG_H))
		return (EXIT_FAILURE);
	if (/*!(core.frame = img_make(IMG_W, IMG_H)) ||*/
			!scene_parse(&core.scene, av[ac - 1]) || !options_parse(&core,
				options_path))
	{
		quit_release(&core);
		return (EXIT_FAILURE);
	}
	scene_has_neg_objects(&core.scene, &core.state_flags);
	if (ocl_init(&core.ocl, &core) != CL_SUCCESS
			|| !(core.frame = img_make(IMG_W, IMG_H)))
	{
		quit_release(&core);
		return (0);
	}
	controller_update(&core.controller);
	event_loop(&core);
	return (EXIT_SUCCESS);
}
