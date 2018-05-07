/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/07 18:48:16 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <stdlib.h>
#include <unistd.h>
#include "rtv1.h"

#include <stdio.h>

int					main(int argc, char **argv)
{
/*	t_img			*img;

	if (!(img = img_make(160, 90)))
	return (-1);
	img_output(img);
	img_release(&img);*/
	t_scene			scene;

	if (argc != 2)
	{
		ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
		return (-1);
	}
	if (!scene_parse(&scene, argv[1]))
		return (-2);
	printf("pos: (%.2f, %.2f, %.2f)\n", scene.cam.pos.x, scene.cam.pos.y, scene.cam.pos.z);
	printf("angle: (%.2f, %.2f, %.2f)\n", scene.cam.angle.x, scene.cam.angle.y, scene.cam.angle.z);
	printf("fov: %.2f\n", scene.cam.fov);
	ft_putendl("everything is fine!");
	objs_release(scene.objs, scene.objs_num);
	return (0);
}
