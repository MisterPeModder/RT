/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:09:46 by jhache            #+#    #+#             */
/*   Updated: 2018/05/29 11:05:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

static void			colorize(
		constant t_light *light,
		float3 lvec,
		t_rt_result *r,
		float3 *c)
{
	float			comp[2];
	float3			tmp;

	tmp = *c;
	comp[1] = dot(r->normal, lvec);
	comp[0] = light->power * comp[1];
	if (comp[1] < 0)
		comp[1] = 0;
	else
		comp[1] = pow(dot((r->normal * (2 * comp[1])) - r->normal,
					lvec), 40) * light->power;
	comp[0] = comp[0] < 0 ? 0 : comp[0];
	comp[1] = comp[1] < 0 ? 0 : comp[1];
	tmp.x += (r->obj->color.x * comp[0] + comp[1]) * light->color.x;
	tmp.y += (r->obj->color.y * comp[0] + comp[1]) * light->color.y;
	tmp.z += (r->obj->color.z * comp[0] + comp[1]) * light->color.z;
	tmp.x = tmp.x > 1.f ? 1.f : tmp.x;
	tmp.y = tmp.y > 1.f ? 1.f : tmp.y;
	tmp.z = tmp.z > 1.f ? 1.f : tmp.z;
	*c = tmp;
}
