/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 09:53:46 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <stdlib.h>
#include <unistd.h>
#include "rtv1.h"

int					main(int argc, char **argv)
{
	t_img			*img;
	t_scene			scene;

	if (argc != 2)
	{
		ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
		return (-1);
	}
	if (!(img = img_make(1600, 900)) || !scene_parse(&scene, argv[1]))
	{
		img_release(&img);
		return (-2);
	}
	if (!render_frame(&scene, img))
	{
		objs_release(scene.objs, scene.objs_num);
		img_release(&img);
		return (-3);
	}
	img_output(img);
	objs_release(scene.objs, scene.objs_num);
	img_release(&img);
	return (0);
}
