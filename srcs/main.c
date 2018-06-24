/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/23 20:25:49 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <unistd.h>
#include "rt.h"

static void			quit_release(t_rt *core)
{
	SDL_FreeSurface(core->frame);
	scene_release(&core->scene);
}

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
	if (!(core.frame = img_make(IMG_W, IMG_H)) ||
			!scene_parse(&core.scene, av[1]) || !options_parse(&core, "./options.json"))
	{
		quit_release(&core);
		return (EXIT_FAILURE);
	}
	scene_has_neg_objects(&core.scene, &core.state_flags);
	if (ocl_init(&core.ocl, &core) != CL_SUCCESS)
	{
		quit_release(&core);
		return (0);
	}
	controller_update(&core.controller);
	event_loop(&core);
	return (EXIT_SUCCESS);
}
