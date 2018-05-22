/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 22:48:38 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/22 19:08:55 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libft_base/io.h>
#include "rt.h"

static int			scene_open(const char *path)
{
	int				fd;
	struct stat		infos;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		perror("Couldn't open file");
		return (-1);
	}
	if (fstat(fd, &infos))
	{
		ft_putendl_fd("Couldn't open file", STDERR_FILENO);
		return (-1);
	}
	if (S_ISDIR(infos.st_mode))
	{
		ft_putendl_fd("Couldn't open file: is a directory", STDERR_FILENO);
		return (-1);
	}
	return (fd);
}

static t_json_value	*scene_read(const char *path)
{
	int					fd;
	t_json_parse_res	*res;
	t_json_value		*obj;

	if ((fd = scene_open(path)) == -1)
		return (NULL);
	if (!(res = json_from_file(fd, JFLAG_ALLOW_COMMENTS | JFLAG_IGNORE_EXTRA)))
	{
		ft_putendl_fd("Couldn't read file", STDERR_FILENO);
		return (NULL);
	}
	close(fd);
	fflush(stdout);
	if (!res->obj)
	{
		ft_putendl_fd(res->err, STDERR_FILENO);
		json_release_file(&res, 1);
		return (NULL);
	}
	obj = res->obj;
	json_release_file(&res, 0);
	return (obj);
}

static int			scene_objs(t_scene *scene, const t_json_array *data)
{
	size_t			i;
	t_json_value	*tmp;

	scene->objs_num = data->values_num;
	add_object_classes(scene->types);
	if (!(scene->objs = malloc(sizeof(t_object) * scene->objs_num)))
		return (0);
	i = 0;
	while (i < scene->objs_num)
	{
		if (!(tmp = json_arr_get(data, i)) || tmp->obj.type != JSON_OBJECT ||
				!obj_make(&scene->objs[i], scene->types, &tmp->obj))
		{
			ft_putstr_fd("Invalid format for object #", STDERR_FILENO);
			ft_putnbr_fd((int)i + 1, STDERR_FILENO);
			ft_putchar_fd('\n', STDERR_FILENO);
			free(scene->objs);
			return (0);
		}
		++i;
	}
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
		vec3f_fill(&scene->bg_color, 0, 0, 0);
	return (1);
}

int					scene_parse(t_scene *scene, const char *path)
{
	t_json_object	*obj;
	t_json_value	*tmp;

	if (!(obj = &(scene_read(path)->obj)))
		return (0);
	if (!(tmp = json_obj_get(obj, "camera")) || tmp->obj.type != JSON_OBJECT ||
			!make_cam(&scene->cam, &tmp->obj))
		return (rel_error("No camera or invalid format", &obj));
	if (!(tmp = json_obj_get(obj, "objects")) || tmp->obj.type != JSON_ARRAY)
		return (rel_error("Invalid objects format", &obj));
	if (!scene_objs(scene, &tmp->arr))
		return (rel_error(NULL, &obj));
	if (!scene_parse2(scene, obj))
		return (0);
	json_release((t_json_value **)&obj);
	return (1);
}
