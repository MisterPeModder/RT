/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 17:44:20 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/11 17:11:18 by jhache           ###   ########.fr       */
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
# define IMG_H 1000

/*
** MIN_IMG_W, MIN_IMG_H: The image's minimal width and height.
*/
# define MIN_IMG_W 150
# define MIN_IMG_H 150

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
** returns: a SDL_Surface representing this image.
*/
SDL_Surface			*img_make(unsigned int w, unsigned int h);

/*
** remake_surfaces: free and reallocate the SDL surface.
** This function is used when the size of the frame change.
*/
int					remake_surfaces(struct s_rt *core);

#endif
