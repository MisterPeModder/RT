/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_load.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 05:46:06 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/23 07:52:41 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_containers/array_list.h>
#include <libft_base/memory.h>
#include "rt.h"
#include "mesh.h"

static void				triangle_to_world(t_mesh_triangle *triangle,
		t_clfloat3 *angle, float scale, t_clfloat3 *pos)
{
	rotate_x(&triangle->p1, angle->x);
	rotate_x(&triangle->p2, angle->x);
	rotate_x(&triangle->p3, angle->x);
	rotate_y(&triangle->p1, angle->y);
	rotate_y(&triangle->p2, angle->y);
	rotate_y(&triangle->p3, angle->y);
	rotate_z(&triangle->p1, angle->z);
	rotate_z(&triangle->p2, angle->z);
	rotate_z(&triangle->p3, angle->z);
	vec3cl_mul(&triangle->p1, scale, &triangle->p1);
	vec3cl_mul(&triangle->p2, scale, &triangle->p2);
	vec3cl_mul(&triangle->p3, scale, &triangle->p3);
	vec3cl_add(&triangle->p1, pos, &triangle->p1);
	vec3cl_add(&triangle->p2, pos, &triangle->p2);
	vec3cl_add(&triangle->p3, pos, &triangle->p3);
}

static int				mesh_face_triangulation(t_arrlst *lst, t_face *face,
		t_mesh_data *data, t_object *object)
{
	int					i;
	t_mesh_triangle		t;
	t_clfloat3			u;
	t_clfloat3			v;

	if (face->verts_num < 3)
		return (1);
	i = -1;
	while (++i < face->verts_num - 2)
	{
		t.p1 = data->vertices[face->verts[0]];
		t.p2 = data->vertices[face->verts[i + 1]];
		t.p3 = data->vertices[face->verts[i + 2]];
		triangle_to_world(&t, &data->angle, data->scale, &object->pos);
		vec3cl_sub(&t.p2, &t.p1, &u);
		vec3cl_sub(&t.p3, &t.p1, &v);
		vec3cl_cross(&u, &v, &t.facing);
		vec3cl_normalize(&t.facing, &t.facing);
		if (!arrlst_add(lst, &t))
			return (0);
	}
	return (1);
}

static void				free_mesh_data(t_mesh_data *data)
{
	int					i;

	free(data->vertices);
	i = -1;
	if (!data->faces)
		return ;
	while (++i < data->faces_num)
		free(data->faces[i].verts);
	free(data->faces);
}

static void				add_scene_triangles(t_scene *scene, t_arrlst *lst)
{
	size_t				old_size;

	old_size = scene->triangles_num;
	if (!(ft_realloc((void **)&scene->mesh_triangles,
					scene->triangles_num * sizeof(t_mesh_triangle),
					(scene->triangles_num += lst->size)
					* sizeof(t_mesh_triangle))))
		scene->triangles_num = 0;
	else if (lst->size > 0)
	{
		ft_memcpy(scene->mesh_triangles + old_size, lst->elements, lst->size
				* sizeof(t_mesh_triangle));
		free(lst->elements);
	}
}

int						mesh_load(t_scene *scene, t_mesh_data *data,
		t_object *object)
{
	t_arrlst			*lst;
	int					i;

	if (!(lst = arrlst_new(sizeof(t_mesh_triangle), 0)))
		return (0);
	i = -1;
	while (++i < data->faces_num)
	{
		if (!mesh_face_triangulation(lst, &data->faces[i], data, object))
		{
			arrlst_del(&lst, NULL, NULL);
			free_mesh_data(data);
			return (0);
		}
	}
	object->props.mesh.num_triangles = lst->size;
	add_scene_triangles(scene, lst);
	free(lst);
	free_mesh_data(data);
	return (1);
}
