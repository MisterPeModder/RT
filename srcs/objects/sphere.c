/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 23:16:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 01:51:02 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					sphere_init(t_object *object, const t_json_object *data)
{
	return (float_from_json(json_obj_get(data, "radius"),
				&object->props.sphere.radius) &&
			object->props.sphere.radius > 0);
}
