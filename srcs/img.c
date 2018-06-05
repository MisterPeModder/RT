/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:11:40 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/05 20:01:40 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include <libft_base/io.h>
#include <stdlib.h>
#include "rt.h"
#include "image.h"

SDL_Surface			*img_make(unsigned int w, unsigned int h)
{
	SDL_Surface		*img;

	if (!(img = SDL_CreateRGBSurfaceWithFormat(0, (int)w, (int)h, 32,
					SDL_PIXELFORMAT_ARGB32)))
		return (NULL);
	SDL_SetSurfaceRLE(img, 1);
	return (img);
}

/*
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
*/
