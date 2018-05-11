/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 10:13:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/11 15:33:20 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				color_fill(t_color color, uint8_t r, uint8_t g, uint8_t b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

/*static uint8_t		cclamp(uint8_t c, float b)
{
	float			r;

	r = (float)c * b;
	if (r > 255)
		return (255);
	return (r < 0.f ? 0 : (uint8_t)r);
}*/

#include <stdio.h>

void				color_brightness(t_color color, t_color src, float factor)
{
	float	r;
	float	g;
	float	b;

	if (factor < 0)
		return ;
	r = (float)color[0] + (float)src[0] * factor;
	g = (float)color[1] + (float)src[1] * factor;
	b = (float)color[2] + (float)src[2] * factor;
	color[0] = ((r > 255) ? 255 : r);
	color[1] = ((g > 255) ? 255 : g);
	color[2] = ((b > 255) ? 255 : b);
}
