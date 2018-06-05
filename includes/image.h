/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 17:44:20 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/05 18:40:08 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>
# include "sdl_defs.h"

/*
** t_color: the color type, color is defined with ARGB format.
*/
typedef union		u_color
{
	int8_t			bytes[4];
	int32_t			value;
}					t_color;

/*
** IMG_W, IMG_H: The image's default width and height.
*/
# define IMG_W 1600
# define IMG_H 900

/*
** color_make: Creates a color from the passed red, green and blue values.
*/
t_color				color_make(int8_t r, int8_t g, int8_t b);

/*
** img_make: Allocates memory for image and initializes it.
**
** -w: image width
** -h: image height
**
** returns: the image.
*/
SDL_Surface			*img_make(unsigned int w, unsigned int h);

/*void				img_pixel_put(t_img *img, t_color c,
  unsigned int x, unsigned int y);*/

/*
** img_release: Frees the passed image.
**
** -mlx: a valid pointer to a t_mlx_ctx structure
*/
/*void				img_release(t **img);*/

#endif
