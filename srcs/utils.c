/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:52:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/07 17:45:20 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

void				*ret_free(void *obj)
{
	if (obj)
		free(obj);
	return (NULL);
}

void				color_fill(t_color color, int8_t r, int8_t g, int8_t b)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
}
