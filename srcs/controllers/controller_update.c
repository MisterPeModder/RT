/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 14:15:23 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/06 14:54:00 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft_base/io.h>
#include "controller.h"

void				controller_update(t_controller *data)
{
	int				i;

	if (data->controller)
		return ;
	i = -1;
	while (++i < SDL_NumJoysticks())
	{
		if (SDL_IsGameController(i))
		{
			if ((data->controller = SDL_GameControllerOpen(i)))
			{
				ft_putstr("Added controller \"");
				ft_putstr(SDL_GameControllerName(data->controller));
				ft_putendl("\"");
				return ;
			}
			ft_putstr_fd("Could not open controller ", STDERR_FILENO);
			ft_putnbr_fd(i, STDERR_FILENO);
			ft_putstr_fd(": ", STDERR_FILENO);
			ft_putendl_fd(SDL_GetError(), STDERR_FILENO);
		}
	}
}
