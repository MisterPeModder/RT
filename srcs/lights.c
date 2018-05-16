/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:38:46 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/16 15:27:46 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft_base/io.h>
#include "rtv1.h"

static int			make_light(t_light *light, const t_json_object *data)
{
	t_json_value	*tmp;

	if (!vec3f_from_json(json_obj_get(data, "pos"), &light->pos))
		return (0);
	if ((tmp = json_obj_get(data, "color")))
	{
		if (!color_from_json(tmp, &light->color))
			return (0);
	}
	else
		vec3f_fill(&light->color, 1, 1, 1);
	if ((tmp = json_obj_get(data, "power")))
	{
		if (!float_from_json(tmp, &light->power))
			return (0);
	}
	else
		light->power = 1;
	return (1);
}

int					scene_lights(t_scene *scene, const t_json_array *data)
{
	size_t			i;
	t_json_value	*tmp;

	scene->lights_num = data->values_num;
	if (!(scene->lights = malloc(sizeof(t_light) * scene->lights_num)))
		return (0);
	i = 0;
	while (i < scene->lights_num)
	{
		if (!(tmp = json_arr_get(data, i)) || tmp->obj.type != JSON_OBJECT
				|| !make_light(&scene->lights[i], &tmp->obj))
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
