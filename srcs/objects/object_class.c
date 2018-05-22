/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_class.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 13:07:31 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/22 19:10:11 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include "rt.h"

static t_obj_class	*make_class(t_obj_class *type, const char *name)
{
	ft_strncpy(type->name, name, OBJ_NAME_SIZE);
	return (type);
}

static void			init_class(t_obj_class *type,
		int (*c)(struct s_object *, const t_json_object *),
		float (*i)(struct s_object *, t_vec3f *, t_vec3f *),
		void (*n)(struct s_object *, t_rt_result *r))
{
	type->construct = c;
	type->intersect = i;
	type->normal = n;
}

void				add_object_classes(t_obj_class *classes)
{
	init_class(make_class(&classes[0], "sphere"), &sphere_init,
			&sphere_intersect, &sphere_normal);
	init_class(make_class(&classes[1], "plane"), NULL, &plane_intersect,
			&plane_normal);
	init_class(make_class(&classes[2], "cone"), &cone_init,
			&cone_intersect, &cone_normal);
	init_class(make_class(&classes[3], "cylinder"), &cylinder_init,
			&cylinder_intersect, &cylinder_normal);
}
