/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 14:27:00 by jloro             #+#    #+#             */
/*   Updated: 2018/06/05 14:31:43 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					triangle_init(t_object *object, const t_json_object *data)
{
	if (!vec3f_from_json(json_obj_get(data, "pos1"),
				&object->props.triangle.pos1))
		return (0);
	if (!vec3f_from_json(json_obj_get(data, "pos2"),
				&object->props.triangle.pos2))
		return (0);
	return (1);
}
