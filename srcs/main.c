/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:41:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/26 17:37:50 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <unistd.h>
#include "rt.h"

int					main(int argc, char **argv)
{
	t_img			*img;
	t_scene			scene;
	t_ocl			ocl;
	int				use_mlx;

	if ((use_mlx = read_args(argc, argv)) == -1)
		return (EXIT_FAILURE);
	if (!(img = img_make(IMG_W, IMG_H)) || !scene_parse(&scene, argv[1]))
	{
		img_release(&img);
		return (EXIT_FAILURE);
	}
	ocl_init(&ocl);
	render_frame(&scene, img);
	scene_release(&scene);
	if (use_mlx)
		img_mlx_output(img);
	else
		img_ppm_output(img);
	return (EXIT_SUCCESS);
}
