/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:52:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/29 11:50:30 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <libft_base/io.h>
#include "rt.h"

void				*ret_free(void *obj)
{
	free(obj);
	return (NULL);
}

int					rel_error(const char *msg, t_json_object **obj)
{
	if (msg)
		ft_putendl_fd(msg, STDERR_FILENO);
	json_release((t_json_value **)obj);
	return (0);
}

void				scene_release(t_scene *scene)
{
	free(scene->objs);
	scene->objs = NULL;
	free(scene->lights);
	scene->lights = NULL;
	if (scene->mesh_triangle != NULL)
	{
		free(scene->mesh_triangle);
		scene->mesh_triangle = NULL;
	}
}

void				scene_has_neg_objects(t_scene *scene, int *state)
{
	size_t			i;

	i = 0;
	while (i < scene->objs_num)
		if (scene->objs[i++].mat.props == MAT_NEGATIVE)
		{
			*state &= ~SF_NO_NEGATIVE;
			return ;
		}
	*state |= SF_NO_NEGATIVE;
}
