/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   meshes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jloro <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 20:20:32 by jloro             #+#    #+#             */
/*   Updated: 2018/06/27 20:48:56 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			mesh_face_free(int **faces, size_t size)
{
	size_t		i;

	i = 0;
	while (i < size)
	{
		free(faces[i]);
		++i;
	}
	free(faces);
}

int				mesh_fail(t_arrlst *triangles, int **faces, size_t len, int i)
{
	if (i)
	{
		arrlst_del(&triangles, NULL);
		return (0);
	}
	else
	{
		mesh_face_free(faces, len);
		return (0);
	}
}

int				calc_coord(t_clfloat3 *point, t_object *object,
		t_arrlst *triangles)
{
	t_clfloat3	tmp;
	t_clfloat3	tmp2;
	t_clfloat3	tmp3;

	vec3cl_mul(&object->facing, point->y, &tmp);
	vec3cl_mul(&object->dir, point->z, &tmp2);
	vec3cl_mul(&object->right, point->x, &tmp3);
	vec3cl_add(&tmp, &tmp2, &tmp);
	vec3cl_add(&tmp, &tmp3, &tmp);
	vec3cl_add(&tmp, &object->pos, point);
	if (!arrlst_add_cpy(triangles, point, sizeof(t_clfloat3)))
	{
		arrlst_del(&triangles, NULL);
		return (0);
	}
	return (1);
}

int				create_triangle(t_scene *scene, t_arrlst *triangles,
		int **faces, size_t *len)
{
	size_t		i[3];

	if (scene->mesh_triangle && !multiple_mesh(scene, len))
		return (0);
	else if (!scene->mesh_triangle && !(scene->mesh_triangle =
				(t_mesh_triangle*)malloc(sizeof(t_mesh_triangle)
			* scene->triangle_total_num)))
		return (0);
	i[0] = 0;
	i[2] = scene->triangle_total_num - len[len[0] + 1];
	while (i[0] < len[0])
	{
		i[1] = 0;
		while (i[1] < len[1 + i[0]] - 2)
		{
			fill_mesh_triangle(scene, triangles, faces, i);
			i[1] += 1;
			i[2] += 1;
		}
		i[0]++;
	}
	return (1);
}
