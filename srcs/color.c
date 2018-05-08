/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 10:13:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/08 11:41:09 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				color_fill(t_color color, uint8_t r, uint8_t g, uint8_t b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

#include <stdio.h>

static uint8_t		cclamp(uint8_t c, float b)
{
	float			r;

	r = (float)c * b;
	if (r > 255)
		return (255);
	return (r < 0 ? 0 : r);
}

void				color_brightness(t_color color, t_color src, float b)
{
	/*b = (b + 1.f) * 20;*/
	color_fill(color, cclamp(src[0], b), cclamp(src[1], b), cclamp(src[2], b));
}
