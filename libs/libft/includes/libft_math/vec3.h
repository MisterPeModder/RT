/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 02:58:32 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 03:18:35 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

typedef struct	s_vec3i
{
	int			x;
	int			y;
	int			z;
}				t_vec3i;

typedef struct	s_vec3f
{
	float		x;
	float		y;
	float		z;
}				t_vec3f;

typedef struct	s_vec3d
{
	double		x;
	double		y;
	double		z;
}				t_vec3d;

/*
** vec3*_fill: fills the 'dst' vector with the passed coordinates.
**
** returns: the 'dst' vector to allow chaining.
*/
t_vec3i			*vec3i_fill(t_vec3i *dst, int x, int y, int z);
t_vec3f			*vec3f_fill(t_vec3f *dst, float x, float y, float z);
t_vec3d			*vec3d_fill(t_vec3d *dst, double x, double y, double z);

/*
** vec3*_cpy: copies the contents of 3d vector 'src' into 'dst'.
**
** returns: the 'dst' vector to allow chaining.
*/
t_vec3i			*vec3i_cpy(const t_vec3i *src, t_vec3i *dst);
t_vec3f			*vec3f_cpy(const t_vec3f *src, t_vec3f *dst);
t_vec3d			*vec3d_cpy(const t_vec3d *src, t_vec3d *dst);

/*
** vec3*_*to*: casts the vector 'src' into the vector 'dst'.
**
** returns: the casted 'dst' vector to allow chaining.
*/
t_vec3f			*vec3_itof(const t_vec3i *src, t_vec3f *dst);
t_vec3d			*vec3_itod(const t_vec3i *src, t_vec3d *dst);
t_vec3i			*vec3_ftoi(const t_vec3f *src, t_vec3i *dst);
t_vec3d			*vec3_ftod(const t_vec3f *src, t_vec3d *dst);
t_vec3i			*vec3_dtoi(const t_vec3d *src, t_vec3i *dst);
t_vec3f			*vec3_dtof(const t_vec3d *src, t_vec3f *dst);

/*
** vec3*_neg: stores the opposite of the vector 'src' into 'dst'.
**
** returns: the 'dst' vector to allow chaining.
*/
t_vec3i			*vec3i_neg(const t_vec3i *src, t_vec3i *dst);
t_vec3f			*vec3f_neg(const t_vec3f *src, t_vec3f *dst);
t_vec3d			*vec3d_neg(const t_vec3d *src, t_vec3d *dst);

/*
** vec3*_add: adds the vectors 'l' and 'r' then stores the result in 'd'.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec3i			*vec3i_add(const t_vec3i *l, const t_vec3i *r, t_vec3i *d);
t_vec3f			*vec3f_add(const t_vec3f *l, const t_vec3f *r, t_vec3f *d);
t_vec3d			*vec3d_add(const t_vec3d *l, const t_vec3d *r, t_vec3d *d);

/*
** vec3*_sub: substracts the vector 'r' to 'l' then stores the result in 'd'.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec3i			*vec3i_sub(const t_vec3i *l, const t_vec3i *r, t_vec3i *d);
t_vec3f			*vec3f_sub(const t_vec3f *l, const t_vec3f *r, t_vec3f *d);
t_vec3d			*vec3d_sub(const t_vec3d *l, const t_vec3d *r, t_vec3d *d);

/*
** vec3*_mul: multiplies the vectors 'l' and 'r' then stores the result in 'd'.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec3i			*vec3i_mul(const t_vec3i *l, int r, t_vec3i *d);
t_vec3f			*vec3f_mul(const t_vec3f *l, float r, t_vec3f *d);
t_vec3d			*vec3d_mul(const t_vec3d *l, double r, t_vec3d *d);

/*
** vec3*_div: divides the vector 'l' with 'r' then stores the result in 'd'.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec3i			*vec3i_div(const t_vec3i *l, int r, t_vec3i *d);
t_vec3f			*vec3f_div(const t_vec3f *l, float r, t_vec3f *d);
t_vec3d			*vec3d_div(const t_vec3d *l, double r, t_vec3d *d);

/*
** vec3*_norm: calculates the norm (length) of a given vector.
*/
float			vec3i_norm(const t_vec3i *vec);
float			vec3f_norm(const t_vec3f *vec);
double			vec3d_norm(const t_vec3d *vec);

/*
** vec3*_normalize: normalizes the vector 'src' and stores the result into dst.
**
** The vec3i version will store its result into a vec3f instead of a vec3i.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec3f			*vec3i_normalize(const t_vec3i *src, t_vec3f *dst);
t_vec3f			*vec3f_normalize(const t_vec3f *src, t_vec3f *dst);
t_vec3d			*vec3d_normalize(const t_vec3d *src, t_vec3d *dst);

/*
** vec3*_dot_product: calculates the dot product of the vectors r and l.
*/
float			vec3i_dot_product(const t_vec3i *r, const t_vec3i *l);
float			vec3f_dot_product(const t_vec3f *r, const t_vec3f *l);
double			vec3d_dot_product(const t_vec3d *r, const t_vec3d *l);

#endif
