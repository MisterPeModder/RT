/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 20:10:02 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/06 20:16:05 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "rtv1.h"

float				to_radians(float deg)
{
	return (M_PI * deg / 180);
}

float				to_degrees(float rad)
{
	return (rad * 180 / M_PI);
}
