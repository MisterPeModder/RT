/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/08 10:13:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/16 14:49:45 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

void				color_fill(t_color color, uint8_t r, uint8_t g, uint8_t b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}

/*
** add_components: Adds the color 'src' to the color 'color'.
**
** -color: where the result is stored
** -src: the color to be added to 'color'
** -comp[2]: the diffuse and specular component
**           (between 0 and 1) of the computed color.
** -light_color: a 3d vector containing the light's color.
*/

static void			add_components(t_color color, t_color src, float comp[2],
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

/*
** colorize: Compute the Diffuse and the Specular components of the color.
**         Colorize is the function which will
**         add those components into one color.
** -light: the light's data structure we are using for computing the color.
** -lvec: a vector which is going from the intersection point
**        to the light coord.
** -r: the primary ray's raytrace result.
** -c: where the color of the pixel will be stored.
*/

void				colorize(t_light light, t_vec3f lvec, t_rt_result *r,
		t_color c)
{
	float			component[2];
	t_vec3f			tmp;

	component[0] = light.power
		* vec3f_dot_product(&lvec, &r->normal);
	component[1] = vec3f_dot_product(&r->normal, &lvec);
	component[1] = component[1] < 0 ? 0 : component[1];
	component[1] = pow(vec3f_dot_product(vec3f_sub(
					vec3f_mul(&r->normal, 2 * component[1], &tmp),
					&r->normal, &tmp), &lvec), 40) * light.power;
	add_components(c, r->obj->color, component, &light.color);
}
