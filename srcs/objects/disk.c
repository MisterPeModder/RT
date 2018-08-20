/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 14:02:22 by jloro             #+#    #+#             */
/*   Updated: 2018/08/20 01:33:06 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					disk_init(t_object *object, const t_json_object *data)
{
	return (float_from_json(json_obj_get(data, "radius"),
				&object->props.sphere.radius)
			&& object->props.sphere.radius > 0);
}
