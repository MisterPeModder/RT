/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_common_structs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:54:11 by jhache            #+#    #+#             */
/*   Updated: 2018/08/23 07:54:30 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_COMMON_STRUCTS_H
# define OCL_COMMON_STRUCTS_H

# include "ocl_types.h"

# define COLOR 1
# define NORMAL 2

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
** -color: its color
** -nfacing: the negative direction vector. Is initialized if 'is_parallel is 1.
** -power: how bright it is
** -is_parallel: if set to 1, tells that this light should be considered as
**               a parallel light.
*/
typedef struct		s_light
{
	t_clfloat3		pos;
	t_clfloat3		color;
	t_clfloat3		facing;
	t_clfloat		power;
	int				is_parallel;
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
	OBJ_DISK,
	OBJ_TRIANGLE,
	OBJ_PARABOLOID,
	OBJ_MESH
}					t_obj_type;

/*
** t_properties: Contains the special properties of objects.
*/
typedef union		u_properties
{
	struct {
		float		radius;
		int			axis;
	}				sphere;
	struct {
		float		opening_angle;
		float		len;
		int			simple;
	}				cone;
	struct {
		float		radius;
		float		len;
	}				cylinder;
	struct {
		t_clfloat3	pos1;
		t_clfloat3	pos2;
	}				triangle;
	struct {
		float		len;
	}				paraboloid;
	struct {
		t_cluint	num_triangles;
		int			is_wobj;
	}				mesh;
}					t_properties;

typedef enum		e_mat_props
{
	MAT_NONE = 0,
	MAT_REFLECTIVE = 1,
	MAT_REFRACTIVE,
	MAT_PORTAL,
	MAT_NEGATIVE
}					t_mat_props;

typedef enum		e_type_noise
{
	NONE = 0,
	WOOD = 1,
	WATER = 2,
	PERLIN = 3,
	SIN_MARBLE = 4,
	LINE_MARBLE = 5
}					t_type_noise;

typedef struct		s_noise
{
	t_clfloat		pers;
	t_clfloat		amp;
	t_clint			octave;
	t_clint			seed;
	t_clint			perturb;
	t_type_noise	type;
}					t_noise;

/*
** -p_out: the portal output coordinates (set if material
**			property is MAT_PORTAL)
*/
typedef struct		s_material
{
	t_clfloat3		p_out;
	t_clfloat		props_coef;
	t_clfloat		refractive_index;
	t_mat_props		props;
	t_noise			noise;
	t_clint			has_noise;
	t_clint			has_shadow;
}					t_material;

typedef struct		s_mesh_triangle
{
	t_clfloat3		p1;
	t_clfloat3		p2;
	t_clfloat3		p3;
	t_clfloat3		facing;
}					t_mesh_triangle;

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
	t_material		mat;
	t_properties	props;
	t_clfloat3		pos;
	t_clfloat3		facing;
	t_clfloat3		dir;
	t_clfloat3		right;
	t_clfloat3		color;
	t_obj_type		type;
}					t_object;

/*
** t_ray_stack: One element of the pseudo-stack in the kernel.
** It stores informations for one reflected or refracted ray.
**
** pos: origin of the ray.
** dir: unit director vector of the ray.
** clr_contribution: how much are we seeing the result of this ray
** This is expressed by a float, between 0 and 1.
*/

typedef struct		s_ray
{
	t_clfloat3		pos;
	t_clfloat3		dir;
	t_clfloat		clr_contrib;
	t_clchar		depth;
}					t_ray;

#endif
