/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_dot_product.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 02:39:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/01 14:26:16 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math/vec2.h"

float			vec2i_dot_product(const t_vec2i *r, const t_vec2i *l)
{
	return (r->x * l->x + r->y * l->y);
}

float			vec2f_dot_product(const t_vec2f *r, const t_vec2f *l)
{
	return (r->x * l->x + r->y * l->y);
}

double			vec2d_dot_product(const t_vec2d *r, const t_vec2d *l)
{
	return (r->x * l->x + r->y * l->y);
}
