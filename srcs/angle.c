/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 20:10:02 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/13 13:01:31 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

/*
** to_radians: Converts degrees to radians.
*/

float				to_radians(float deg)
{
	return (M_PI * deg / 180);
}

/*
** to_degrees: converts radians to degrees.
*/

float				to_degrees(float rad)
{
	return (rad * 180 / M_PI);
}
