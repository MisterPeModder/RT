/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_common_structs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:54:11 by jhache            #+#    #+#             */
/*   Updated: 2018/06/01 15:25:23 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_COMMON_STRUCTS_H
# define OCL_COMMON_STRUCTS_H

# include "ocl_types.h"

/*
** t_cam: The camera
**
** -pos: where the cam is located
** -angle: its angle
** -fov: the field of view
*/
typedef struct		s_cam
{
	t_clfloat3		pos;
	t_clfloat3		angle;
	t_clfloat		fov;
}					t_cam;

/*
** t_light: Represents a light.
**
** -pos: its location
** -power: how bright it is
** -color: its color
*/
typedef struct		s_light
{
	t_clfloat3		pos;
	t_clfloat3		color;
	t_clfloat		power;
}					t_light;

/*
** t_obj_type: Contains each type of object currently available.
*/
typedef enum		e_obj_type
{
	OBJ_PLANE = 1,
	OBJ_SPHERE,
	OBJ_CONE,
	OBJ_CYLINDER,
	OBJ_DISK
}					t_obj_type;

/*
** t_properties: Contains the special properties of objects.
*/
typedef union		u_properties
{
	struct {
		float		radius;
	}				sphere;
	struct {
		float		opening_angle;
		int			simple;
		float		len;
	}				cone;
	struct {
		float		radius;
		float		len;
	}				cylinder;
}					t_properties;

/*
** t_object: Stores all the info about an object instance.
**
** -type: its type, see the t_obj_type enum for more info.
** -pos: where the object is located.
** -facing: its orientation.
** -color: are you really asking ?
** -props: the properties of this object.
*/
typedef struct		s_object
{
	t_obj_type		type;
	t_clfloat3		pos;
	t_clfloat3		facing;
	t_clfloat3		color;
	t_properties	props;
}					t_object;

#endif
