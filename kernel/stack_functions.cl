/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_functions.cl                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 16:03:47 by jhache            #+#    #+#             */
/*   Updated: 2018/06/18 14:27:11 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static inline t_ray	stack_pop(
	local t_ray *stack,
	t_cluint *stack_size,
	t_cluint offset
	)
{
	*stack_size -= 1;
	return (*(stack + offset + *stack_size));
}

static inline void			stack_push(
	local t_ray *stack,
	t_ray new,
	t_cluint *stack_size,
	t_cluint offset
	)
{
	*(stack + *stack_size + offset) = new;
	*stack_size += 1;
}
