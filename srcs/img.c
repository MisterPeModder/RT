/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:11:40 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 14:00:06 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include <libft_base/io.h>
#include <stdlib.h>
#include "rt.h"
#include "image.h"
#include "mlx_defs.h"

t_img				*img_make(t_mlx_ctx *mlx, unsigned int w, unsigned int h)
{
	t_img			*img;
	int				bpp;

	if (!mlx || !(img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	img->w = w;
	img->h = h;
	if (!(img->mlx_img = mlx_new_image(mlx->mlx_ptr, (int)w, (int)h)))
		return (ret_free(img));
	if (!(img->data = (t_color *)mlx_get_data_addr(img->mlx_img, &bpp,
					&img->line_size, &img->endian)))
		return (ret_free(img));
	img->line_size /= 4;
	return (img);
}

void				img_pixel_put(t_img *img, t_color c,
		unsigned int x, unsigned int y)
{
	unsigned int	pos;

	pos = x + y * (unsigned int)img->line_size;
	if (img->endian)
	{
		img->data[pos].bytes[0] = 0;
		img->data[pos].bytes[1] = c.bytes[1];
		img->data[pos].bytes[2] = c.bytes[2];
		img->data[pos].bytes[3] = c.bytes[3];
	}
	else
	{
		img->data[pos].bytes[3] = 0;
		img->data[pos].bytes[2] = c.bytes[1];
		img->data[pos].bytes[1] = c.bytes[2];
		img->data[pos].bytes[0] = c.bytes[3];
	}
}

void				img_release(t_mlx_ctx *mlx, t_img **img)
{
	if (!img || !*img)
		return ;
	if ((*img)->mlx_img)
		mlx_destroy_image(mlx->mlx_ptr, (*img)->mlx_img);
	free(*img);
	*img = NULL;
}
