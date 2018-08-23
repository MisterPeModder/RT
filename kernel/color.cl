/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.cl                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:09:46 by jhache            #+#    #+#             */
/*   Updated: 2018/08/23 03:52:38 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline void	set_to_zero(float3 *vec)
{
	(*vec).x = 0;
	(*vec).y = 0;
	(*vec).z = 0;
}

static void			add_color(float3 *source, float3 addition)
{
	addition += *source;
	addition.x = addition.x > 1.f ? 1.f : addition.x;
	addition.y = addition.y > 1.f ? 1.f : addition.y;
	addition.z = addition.z > 1.f ? 1.f : addition.z;
	*source = addition;
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

static void			colorize(
		constant t_light *light,
		float3 lvec,
		t_rt_result *r,
		float3 *c,
		float3 transparency_coef
	)
{
	float			comp[2];
	float3			tmp;

	comp[1] = dot(r->normal, lvec);
	comp[0] = light->power * comp[1] * (1.f - r->obj->mat.props_coef);
	if (comp[1] < 0)
		comp[1] = 0;
	else
		comp[1] = pow(dot((r->normal * (2 * comp[1])) - r->normal,
					lvec), 42) * light->power;
	comp[0] = comp[0] < 0 ? 0 : comp[0];
	comp[1] = comp[1] < 0 ? 0 : comp[1];
	tmp.x = (r->obj->color.x * comp[0] + comp[1]) * light->color.x;
	tmp.y = (r->obj->color.y * comp[0] + comp[1]) * light->color.y;
	tmp.z = (r->obj->color.z * comp[0] + comp[1]) * light->color.z;
	tmp *= transparency_coef;
	add_color(c, tmp);
}
