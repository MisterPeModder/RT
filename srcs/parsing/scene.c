/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 22:48:38 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/06 18:50:40 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft_base/io.h>
#include <libft_base/memory.h>
#include <libft_base/stringft.h>
#include "rt.h"

static void			init_empty_mesh(t_scene *scene)
{
	scene->triangle_total_num = 1;
	scene->mesh_triangle = (t_mesh_triangle*)malloc(sizeof(t_mesh_triangle));
	ft_bzero((void*)scene->mesh_triangle, sizeof(t_mesh_triangle));
}


static int			scene_objs(t_scene *scene, const t_json_array *data)
{
	size_t			i;
	t_json_value	*tmp;

	scene->objs_num = data->values_num;
	scene->triangle_total_num = 0;
	if (!(scene->objs = malloc(sizeof(t_object) * scene->objs_num)))
		return (0);
	i = 0;
	while (i < scene->objs_num)
	{
		if (!(tmp = json_arr_get(data, i)) || tmp->obj.type != JSON_OBJECT ||
				!obj_make(scene, &scene->objs[i], &tmp->obj))
		{
			ft_putstr_fd("Invalid format for object #", STDERR_FILENO);
			ft_putnbr_fd((int)i + 1, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			free(scene->objs);
			scene->objs = NULL;
			return (0);
		}
		++i;
	}
	if (scene->triangle_total_num == 0)
		init_empty_mesh(scene);
	return (1);
}

static int			scene_parse2(t_scene *scene, t_json_object *obj)
{
	t_json_value	*tmp;

	if (!(tmp = json_obj_get(obj, "lights")) || tmp->obj.type != JSON_ARRAY)
	{
		free(scene->objs);
		return (rel_error("No lights or invalid format", &obj));
	}
	if (!scene_lights(scene, &tmp->arr))
	{
		free(scene->objs);
		return (rel_error(NULL, &obj));
	}
	if ((tmp = json_obj_get(obj, "background_color")))
	{
		if (!color_from_json(tmp, &scene->bg_color))
		{
			free(scene->objs);
			return (rel_error("Invalid background color", &obj));
		}
	}
	else
		vec3cl_fill(&scene->bg_color, 0, 0, 0);
	json_release((t_json_value **)&obj);
	return (1);
}

int					scene_parse(t_scene *scene, const char *path)
{
	t_json_object	*obj;
	t_json_value	*tmp;

	if (!(obj = &(json_file_read(path)->obj)))
		return (0);
	if (!(tmp = json_obj_get(obj, "camera")) || tmp->obj.type != JSON_OBJECT ||
			!make_cam(&scene->cam, &tmp->obj))
		return (rel_error("No camera or invalid format", &obj));
	scene->depth = 0;
	scene->filter = FILTER_NONE;
	if ((tmp = json_obj_get(obj, "depth")))
	{
		if (tmp->n_i.type != JSON_INT || (scene->depth = tmp->n_i.value) < 0)
			return (rel_error("The depth must be a positive integer", &obj));
	}
	if (!(tmp = json_obj_get(obj, "objects")) || tmp->obj.type != JSON_ARRAY)
		return (rel_error("Invalid objects format", &obj));
	if (!scene_objs(scene, &tmp->arr))
		return (rel_error(NULL, &obj));
	if (!scene_parse2(scene, obj))
		return (0);
	return (1);
}
