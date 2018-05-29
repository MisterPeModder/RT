/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 14:04:06 by jhache            #+#    #+#             */
/*   Updated: 2018/05/29 01:51:28 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					cylinder_init(t_object *object, const t_json_object *data)
{
	if (!float_from_json(json_obj_get(data, "radius"),
				&object->props.cylinder.radius))
		return (0);
	return (1);
}
