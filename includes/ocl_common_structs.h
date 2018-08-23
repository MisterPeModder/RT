/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_common_structs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:54:11 by jhache            #+#    #+#             */
/*   Updated: 2018/08/23 01:38:58 by jloro            ###   ########.fr       */
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
		int			simple;
		float		len;
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
		size_t		num_triangles;
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

/* !!! THIS COMMENT IS A MEMO FOR THE KERNEL COMMENT, IT SHOULD BE DELETED
** Noise struct.
** -c1, c2 and c3 are colors for material perturbation.
** -amp is amplitude used by noise function.
** -fin is incremented in noise function by the noise value.
** -div divide fin at the end of all noise depth.
** -freq is the frequence used by the noise function.
** -depth of the noise.
** -lines of marble perturbation method.
** -value and value1 for intermediate sin/cos and material perturbations.
** -result to store material perturbations.
** -threshold for wood material method.
** -perturbation for marble perturbation method.
** -a to d for lerp the noise.
** -i to increment the depth of the noise.
** -s to z for noise transformation of x, y and z.
** -xa, ya, za, x_int, y_int, z_int, x_frac, y_frac and z_frac diverse
** var to manipulate x, y and z through different types, etc..
** -low and high to smooth the shape of the function by his mix and max values.
*/

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
**         property is MAT_PORTAL)
*/
typedef struct		s_material
{
//	t_clfloat		shininess;//maybe for specular
	t_mat_props		props;
	t_clfloat		props_coef;
	t_clfloat		refractive_index;
	t_noise			noise;
	t_clfloat3		p_out;
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
	t_obj_type		type;
	t_clfloat3		pos;
	t_clfloat3		facing;
	t_clfloat3		dir;
	t_clfloat3		right;
	t_clfloat3		color;
	t_properties	props;
	t_material		mat;
}					t_object;

/*
** t_ray_stack: One element of the pseudo-stack in the kernel.
** It stores informations for one reflected or refracted ray.
**
** pos: origin of the ray.
** dir: unit director vector of the ray.
** clr_contribution: how much are we seeing the result of the ray ?
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
