/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 10:13:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/16 13:50:40 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void				color_fill(t_color color, uint8_t r, uint8_t g, uint8_t b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

void				colorize(t_color color, t_color src, float comp[2],
		t_vec3f *light_color)
{
	float	r;
	float	g;
	float	b;
	t_vec3f	s_color;

	vec3f_fill(&s_color, src[0], src[1], src[2]);
	vec3f_div(&s_color, 255, &s_color);
	comp[0] = comp[0] < 0 ? 0 : comp[0];
	comp[1] = comp[1] < 0 ? 0 : comp[1];
	r = (float)color[0] + (s_color.x * comp[0] + comp[1]) * light_color->x
		* 255;
	g = (float)color[1] + (s_color.y * comp[0] + comp[1]) * light_color->y
		* 255;
	b = (float)color[2] + (s_color.z * comp[0] + comp[1]) * light_color->z
		* 255;
	color[0] = ((r > 255) ? 255 : r);
	color[1] = ((g > 255) ? 255 : g);
	color[2] = ((b > 255) ? 255 : b);
}
