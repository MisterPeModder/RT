/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wobj_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 06:44:29 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/22 07:19:07 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "ocl_types.h"
#include <libft_base/io.h>
#include <libft_base/character.h>
#include <libft_base/stringft.h>
#include <libft_containers/array_list.h>

static int		parse_wobj_vertex_coord(const char **line, t_clfloat *dst)
{
	while (ft_isspace(**line))
		++*line;
	if (!ft_strisdouble(*line))
		return (0);
	*dst = (t_clfloat)ft_atod(*line);
	if (**line == '-' || **line == '+')
		++*line;
	while (**line && ft_isdigit(**line))
		++*line;
	if (**line == '.')
	{
		++*line;
		while (ft_isdigit(**line))
			++*line;
	}
	return (1);
}

int				parse_wobj_vertex(const char *line, t_arrlst *vertices)
{
	t_clfloat3	vertex;

	++line;
	if (!parse_wobj_vertex_coord(&line, &vertex.x)
			|| !parse_wobj_vertex_coord(&line, &vertex.y)
			|| !parse_wobj_vertex_coord(&line, &vertex.z))
	{
		ft_putstr_fd(".obj vertex #", STDERR_FILENO);
		ft_putnbr_fd((int)vertices->size + 1, STDERR_FILENO);
		ft_putendl_fd(" is invalid", STDERR_FILENO);
		return (0);
	}
	return (arrlst_add(vertices, &vertex));
}

static void		ignore_extra_args(const char **line)
{
	if (**line == '/')
		while (ft_isdigit(*(++*line)))
			;
	if (**line == '/')
		while (ft_isdigit(*(++*line)))
			;
}

int				parse_wobj_face(const char *line, t_arrlst *faces)
{
	t_face		face;
	t_arrlst	*indexes;
	int			index;

	if (!(indexes = arrlst_new(sizeof(int), 0)))
		return (0);
	++line;
	while (*line)
	{
		while (ft_isspace(*line))
			++line;
		if (!ft_strisint(line) || ((index = ft_atoi(line)) * 0 + 1
					&& !arrlst_add(indexes, &index)))
		{
			arrlst_del(&indexes, NULL, NULL);
			return (0);
		}
		while (ft_isdigit(*line))
			++line;
		ignore_extra_args(&line);
	}
	face.verts = indexes->elements;
	face.verts_num = (int)indexes->size;
	free(indexes);
	return (arrlst_add(faces, &face));
}
