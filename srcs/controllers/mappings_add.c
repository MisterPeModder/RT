/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mappings_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 11:00:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/08 17:43:32 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include "rt.h"

int						add_sdl_mappings(const t_json_array *mappings)
{
	size_t				i;
	t_json_value		*tmp;

	i = 0;
	while (i < mappings->values_num)
	{
		tmp = json_arr_get(mappings, i);
		if (!tmp || tmp->str.type != JSON_STRING)
			return (0);
		if (SDL_GameControllerAddMapping(tmp->str.value) == -1)
		{
			ft_putstr("Failed to add controller mapping: ");
			ft_putendl(SDL_GetError());
			return (0);
		}
		++i;
	}
	return (1);
}
