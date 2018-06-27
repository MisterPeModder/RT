/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teleport_ray.cl                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 03:28:44 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/27 06:50:13 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define TP_BIAS 0.001f

static void			teleport_ray(
		t_ray curr_ray,
		t_rt_result *r,
		local t_ray *stack,
		t_cluint *stack_size,
		t_cluint offset
		)
{
	t_ray			tmp;

	if (curr_ray.depth <= 0)
		return ;
	tmp.dir = curr_ray.dir;
	//Fixes "shadow acne" when two portal of the same size are linked together.
	tmp.pos = r->obj->mat.p_out - tmp.dir * TP_BIAS;
	tmp.clr_contrib = curr_ray.clr_contrib;
	tmp.depth = curr_ray.depth - 1;
	stack_push(stack, tmp, stack_size, offset);
}
