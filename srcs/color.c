/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 10:13:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/12 18:09:28 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				color_fill(t_color color, uint8_t r, uint8_t g, uint8_t b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void				colorize(t_color color, t_color src, float comp[2])
{
	float	r;
	float	g;
	float	b;
	float	factor;

	factor = ((comp[0] > 0/* && comp[0] < 1*/) ? comp[0] : 0);
	factor += ((comp[1] > 0/* && comp[1] < 1*/) ? comp[1] : 0);
	r = (float)color[0] + (float)src[0] * factor;
	g = (float)color[1] + (float)src[1] * factor;
	b = (float)color[2] + (float)src[2] * factor;
	color[0] = ((r > 255) ? 255 : r);
	color[1] = ((g > 255) ? 255 : g);
	color[2] = ((b > 255) ? 255 : b);
}
