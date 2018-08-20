/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:11:40 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/20 17:08:16 by jhache           ###   ########.fr       */
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
					IMAGE_FORMAT)))
		return (NULL);
	return (img);
}
