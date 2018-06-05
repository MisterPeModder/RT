/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 20:10:02 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 01:28:14 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rt.h"

/*
** to_radians: Converts degrees to radians.
*/

t_clfloat				to_radians(t_clfloat deg)
{
	return (M_PI * deg / 180);
}

/*
** to_degrees: converts radians to degrees.
*/

t_clfloat				to_degrees(t_clfloat rad)
{
	return (rad * 180 / M_PI);
}
