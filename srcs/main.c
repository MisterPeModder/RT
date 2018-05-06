/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/07 00:37:06 by yguaye           ###   ########.fr       */
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
	t_json_value	*obj;
	t_cam			cam;

	if (argc != 2)
	{
		ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
		return (-1);
	}
	if (!(obj = scene_read(argv[1])))
		return (-2);
	if (!make_cam(&cam, &obj->obj))
	{
		ft_putendl_fd("Invalid camera format", STDERR_FILENO);
		json_release(&obj);
		return (-3);
	}
	json_release(&obj);
	printf("pos: (%.2f, %.2f, %.2f)\n", cam.pos.x, cam.pos.y, cam.pos.z);
	printf("angle: (%.2f, %.2f, %.2f)\n", cam.angle.x, cam.angle.y, cam.angle.z);
	printf("fov: %.2f\n", cam.fov);
	ft_putendl("everything is fine!");
	return (0);
}
