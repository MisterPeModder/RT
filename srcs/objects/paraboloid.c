/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paraboloid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/08 13:35:37 by jloro             #+#    #+#             */
/*   Updated: 2018/08/20 01:33:19 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			paraboloid_init(t_object *object, const t_json_object *data)
{
	return (float_from_json(json_obj_get(data, "length"),
				&object->props.paraboloid.len)
			&& object->props.paraboloid.len > 0);
}
