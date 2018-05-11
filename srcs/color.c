/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 10:13:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/11 14:24:55 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				color_fill(t_color color, uint8_t r, uint8_t g, uint8_t b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

static uint8_t		cclamp(uint8_t c, float b)
{
	float			r;

	r = (float)c * b;
	if (r > 255)
		return (255);
	return (r < 0.f ? 0 : (uint8_t)r);
}

#include <stdio.h>

void				color_brightness(t_color color, t_color src, float b)
{
	color[0] += cclamp(src[0], b);
	color[1] += cclamp(src[1], b);
	color[2] += cclamp(src[2], b);
}
