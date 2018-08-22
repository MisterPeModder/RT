/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 04:25:53 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/20 04:47:13 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"

int			parse_mesh(struct s_scene *scene, t_object *object,
		const t_json_object *data)
{
	return (object->props.mesh.is_wobj
			? parse_wobj_mesh(scene, object, data)
			: parse_json_mesh(scene, object, data));
}
