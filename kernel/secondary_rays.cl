/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondary_rays.cl                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 11:18:56 by jhache            #+#    #+#             */
/*   Updated: 2018/06/25 11:40:58 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static t_ray		cast_reflection(t_ray incident_ray, t_rt_result *r)
{
	t_ray			reflected_ray;

	reflected_ray.pos = r->pos;
	reflected_ray.dir = incident_ray.dir - 2 * r->normal
		* dot(incident_ray.dir, r->normal);
	reflected_ray.pos += reflected_ray.dir * 0.001f;
	reflected_ray.depth = incident_ray.depth - 1;
	return (reflected_ray);
}

static t_ray		cast_refraction(t_ray incident_ray, t_rt_result *r)
{
	t_ray			refracted_ray;
	float			refractive_coef;
	float			tmp;
	float			tmp2;
	t_clfloat3		n;

	n = r->normal;
	tmp = dot(incident_ray.dir, n);
	if (tmp < 0.f)
	{
		tmp *= -1;
		refractive_coef = 1.00029f / r->obj->mat.refractive_index;
	}
	else
	{
		refractive_coef = r->obj->mat.refractive_index / 1.00029f;
		n *= -1;
	}
	if (tmp > 1.f)
		tmp = 1.f;
	tmp2 = 1 - refractive_coef * refractive_coef * (1.f - tmp * tmp);
	if (tmp2 < 0)
	{
		refracted_ray.depth = 0;
		return (refracted_ray);
	}
	refracted_ray.dir = refractive_coef * incident_ray.dir
		+ (refractive_coef * tmp - sqrt(tmp2)) * n;
	refracted_ray.pos = r->pos;
	refracted_ray.pos += refracted_ray.dir * 0.001f;
	refracted_ray.depth = incident_ray.depth - 1;
	return (refracted_ray);
}

static float		schlick_equation(
	t_ray incident_ray,
	t_rt_result *r
	)
{
	float			result;
	float			tmp;
	float			tmp2;
	float			doti;

	doti = dot(r->normal, incident_ray.dir);
	if (doti >= 0.f)
		tmp = 1.00029f - r->obj->mat.refractive_index;
	else
		tmp = r->obj->mat.refractive_index - 1.00029f;
	tmp2 = 1.00029f + r->obj->mat.refractive_index;
	tmp = tmp / tmp2;
	tmp *= tmp;
	if ((doti >= 0)
			? (1.00029f > r->obj->mat.refractive_index)
			: (1.00029f < r->obj->mat.refractive_index))
	{
		tmp2 = 1.00029f / r->obj->mat.refractive_index;
		tmp2 = ((doti < 0) ? tmp2 * tmp2 : 1 / (tmp2 * tmp2)) * (1.f - doti * doti);
		if (tmp2 > 1.f)
			return (1.f);
		tmp2 = sqrt(1.f - tmp2);
	}
	else
		tmp2 = ((doti < 0) ? -doti : doti);
	result = tmp + (1.f - tmp) * pow(1.f - tmp2, 5);
	return (result);
}

static void			compute_secondary_rays(
	t_ray incident_ray,
	t_rt_result *r,
	local t_ray *stack,
	t_cluint *stack_size,
	t_cluint offset
	)
{
	t_ray			tmp;
	float			reflection_coef;

	reflection_coef = schlick_equation(incident_ray, r);
	if (reflection_coef < 1.f && r->obj->mat.props == MAT_REFRACTIVE)
	{
		tmp = cast_refraction(incident_ray, r);
		tmp.clr_contrib = (1.f - reflection_coef) * r->obj->mat.props_coef
			* incident_ray.clr_contrib;
		if (tmp.depth >= 0 && tmp.clr_contrib > 0.01f)
			stack_push(stack, tmp, stack_size, offset);
	}
	tmp = cast_reflection(incident_ray, r);
	if (r->obj->mat.props == MAT_REFRACTIVE)
		tmp.clr_contrib = r->obj->mat.props_coef * reflection_coef;
	else
		tmp.clr_contrib = (1 - r->obj->mat.props_coef) * reflection_coef
			+ r->obj->mat.props_coef;
	tmp.clr_contrib *= incident_ray.clr_contrib;
	if (tmp.depth >= 0 && tmp.clr_contrib > 0.01f)
		stack_push(stack, tmp, stack_size, offset);
}
