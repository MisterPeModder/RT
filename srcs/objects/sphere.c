/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 23:16:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/22 10:53:16 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include "rt.h"

int					sphere_init(t_object *object, const t_json_object *data)
{
	t_json_value	*tmp;

	if (!float_from_json(json_obj_get(data, "radius"),
				&object->props.sphere.radius) ||
			object->props.sphere.radius < 0)
		return (0);
	if ((tmp = json_obj_get(data, "cut")))
	{
		if (tmp->str.type != JSON_STRING)
			return (0);
		if (ft_strequ(tmp->str.value, "z axis"))
			object->props.sphere.axis = 0;
		else if (ft_strequ(tmp->str.value, "x axis"))
			object->props.sphere.axis = 1;
		else if (ft_strequ(tmp->str.value, "y axis"))
			object->props.sphere.axis = 2;
		else
			return (0);
	}
	else
		object->props.sphere.axis = -1;
	return (1);
}
