/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/24 04:48:03 by jhache            #+#    #+#             */
/*   Updated: 2018/08/21 19:46:51 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL_ttf.h>
#include "rt.h"
#include "move.h"
#include <libft_base/io.h>

static void			depth_change(int key, t_rt *core)
{
	if (key == SDLK_KP_PLUS)
	{
		core->scene.depth += 1;
		if (compute_work_size(&core->mem_info, core) != CL_SUCCESS
			|| init_frame_kernel_arg(&core->ocl, core) != CL_SUCCESS)
			exit_rt(core);
		if (!(remake_surfaces(core)))
			exit_rt(core);
		core->state_flags |= SF_SHOULD_UPDATE;
		core->sample_count = core->sample_nb;
	}
	else if (key == SDLK_KP_MINUS && core->scene.depth > 0)
	{
		core->scene.depth -= 1;
		if (compute_work_size(&core->mem_info, core) != CL_SUCCESS
				|| init_frame_kernel_arg(&core->ocl, core) != CL_SUCCESS)
			exit_rt(core);
		if (!(remake_surfaces(core)))
			exit_rt(core);
		core->state_flags |= SF_SHOULD_UPDATE;
		core->sample_count = core->sample_nb;
	}
}

static void			sample_change(int key, t_rt *core)
{
	if (key == SDLK_EQUALS && core->sample_nb < 20)
	{
		core->sample_nb += 1;
		core->sample_count += 1;
		core->state_flags |= SF_SHOULD_UPDATE;
	}
	else if (key == SDLK_MINUS && core->sample_nb > 1)
	{
		core->sample_nb -= 1;
		core->sample_count = ((core->sample_count <= 1)
				? core->sample_nb : core->sample_count - 1);
		core->state_flags |= SF_SHOULD_UPDATE;
	}
}

void				key_handling(int key, t_rt *core)
{
	if (key == SDLK_ESCAPE)
		exit_rt(core);
	else if (key == SDLK_h)
	{
		core->sdl.show_ui = !core->sdl.show_ui;
		print_frame(core, NULL);
	}
	else if ((key == SDLK_1 || key == SDLK_2 || key == SDLK_3 || key == SDLK_4
				|| key == SDLK_5 || key == SDLK_6 || key == SDLK_0)
			&& core->scene.filter != key)
	{
		core->scene.filter = (t_filter)key;
		print_frame(core, NULL);
	}
	else if (key == SDLK_EQUALS || key == SDLK_MINUS)
		sample_change(key, core);
	else
		depth_change(key, core);
}
