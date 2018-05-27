/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 17:44:20 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 14:25:09 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H

# include <stdint.h>
# include "mlx_defs.h"

/*
** t_color: the color type, color is defined with ARGB format.
*/
typedef union		u_color
{
	int8_t			bytes[4];
	int32_t			value;
}					t_color;

/*
** IMG_W, IMG_H: The image's width and height.
*/
# define IMG_W 1200
# define IMG_H 675

/*
** t_img: The frame buffer
**
** -w: the image width
** -h: the image height
** -data: A bidimensional array of colors
*/
typedef struct		s_img
{
	unsigned int	w;
	unsigned int	h;
	void			*mlx_img;
	t_color			*data;
	int				line_size;
	int				endian;
}					t_img;

/*
** color_make: Creates a color from the passed red, green and blue values.
*/
t_color				color_make(int8_t r, int8_t g, int8_t b);

/*
** img_make: Allocates memory for image and initializes it.
**
** -mlx: a valid pointer to a t_mlx_ctx structure
** -w: image width
** -h: image height
**
** returns: the image.
*/
t_img				*img_make(t_mlx_ctx *mlx, unsigned int w, unsigned int h);

void				img_pixel_put(t_img *img, t_color c,
		unsigned int x, unsigned int y);

/*
** img_release: Frees the passed image.
**
** -mlx: a valid pointer to a t_mlx_ctx structure
*/
void				img_release(t_mlx_ctx *mlx, t_img **img);

#endif
