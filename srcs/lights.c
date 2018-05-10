/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:38:46 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 18:48:01 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft_base/io.h>
#include "rtv1.h"

int					scene_lights(t_scene *scene, const t_json_array *data)
{
	size_t			i;

	scene->lights_num = data->values_num;
	if (!(scene->lights = malloc(sizeof(t_vec3f) * scene->lights_num)))
		return (0);
	i = 0;
	while (i < scene->lights_num)
	{
		if (!vec3f_from_json(json_arr_get(data, i), &scene->lights[i]))
		{
			ft_putstr_fd("Invalid format for light #", STDERR_FILENO);
			ft_putnbr_fd((int)i + 1, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			free(scene->lights);
			return (0);
		}
		++i;
	}
	return (1);
}
