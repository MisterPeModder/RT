/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 22:48:38 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/07 00:03:45 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <libft_base/io.h>
#include "rtv1.h"

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

t_json_value		*scene_read(const char *path)
{
	int					fd;
	t_json_parse_res	*res;
	t_json_value		*obj;

	if ((fd = scene_open(path)) == -1)
		return (NULL);
	if (!(res = json_from_file(fd, JFLAG_ALLOW_COMMENTS)))
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
