/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_common_structs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 18:54:11 by jhache            #+#    #+#             */
/*   Updated: 2018/06/29 11:34:59 by yguaye           ###   ########.fr       */
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

typedef enum		e_type_mat
{
	WOOD = 1,
	WATER = 2,
	PERLIN = 3,
	SIN_MARBLE = 4,
	LINE_MARBLE = 5,
	NONE = 6
}					t_type_mat;

/*
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
typedef struct	s_noise
{
	t_clint		has_noise;
	t_clfloat	freq;
	t_clint		depth;
	t_clint		seed;
	t_type_mat	type;
	t_clint		hash[256];
	t_clfloat3	c1;
	t_clfloat3	c2;
	t_clfloat3	c3;
	t_clfloat	amp;
	t_clfloat	fin;
	t_clfloat	div;
	t_clint		lines;
	t_clfloat	value;
	t_clfloat	value1;
	t_clfloat3	result;
	t_clfloat	threshold;
	t_clfloat	perturbation;
	t_clint		a;
	t_clint		b;
	t_clint		c;
	t_clint		d;
	t_clint		i;
	t_clint		s;
	t_clint		t;
	t_clint		u;
	t_clint		v;
	t_clint		w;
	t_clint		x;
	t_clint		y;
	t_clint		z;
	t_clfloat	xa;
	t_clfloat	ya;
	t_clfloat	za;
	t_clfloat	low;
	t_clfloat	high;
	t_clint		x_int;
	t_clint		y_int;
	t_clint		z_int;
	t_clfloat	x_frac;
	t_clfloat	y_frac;
	t_clfloat	z_frac;
}				t_noise;

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
	t_noise			*noise;
	t_clfloat3		p_out;
	int				has_shadow;
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
