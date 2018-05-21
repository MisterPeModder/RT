/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 00:01:04 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 02:58:45 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC2_H
# define VEC2_H

typedef struct	s_vec2i
{
	int			x;
	int			y;
}				t_vec2i;

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct	s_vec2d
{
	double		x;
	double		y;
}				t_vec2d;

/*
** vec2*_fill: fills the 'dst' vector with the passed coordinates.
**
** returns: the 'dst' vector to allow chaining.
*/
t_vec2i			*vec2i_fill(t_vec2i *dst, int x, int y);
t_vec2f			*vec2f_fill(t_vec2f *dst, float x, float y);
t_vec2d			*vec2d_fill(t_vec2d *dst, double x, double y);

/*
** vec2*_cpy: copies the contents of 2d vector 'src' into 'dst'.
**
** returns: the 'dst' vector to allow chaining.
*/
t_vec2i			*vec2i_cpy(const t_vec2i *src, t_vec2i *dst);
t_vec2f			*vec2f_cpy(const t_vec2f *src, t_vec2f *dst);
t_vec2d			*vec2d_cpy(const t_vec2d *src, t_vec2d *dst);

/*
** vec2*_*to*: casts the vector 'src' into the vector 'dst'.
**
** returns: the casted 'dst' vector to allow chaining.
*/
t_vec2f			*vec2_itof(const t_vec2i *src, t_vec2f *dst);
t_vec2d			*vec2_itod(const t_vec2i *src, t_vec2d *dst);
t_vec2i			*vec2_ftoi(const t_vec2f *src, t_vec2i *dst);
t_vec2d			*vec2_ftod(const t_vec2f *src, t_vec2d *dst);
t_vec2i			*vec2_dtoi(const t_vec2d *src, t_vec2i *dst);
t_vec2f			*vec2_dtof(const t_vec2d *src, t_vec2f *dst);

/*
** vec2*_neg: stores the opposite of the vector 'src' into 'dst'.
**
** returns: the 'dst' vector to allow chaining.
*/
t_vec2i			*vec2i_neg(const t_vec2i *src, t_vec2i *dst);
t_vec2f			*vec2f_neg(const t_vec2f *src, t_vec2f *dst);
t_vec2d			*vec2d_neg(const t_vec2d *src, t_vec2d *dst);

/*
** vec2*_add: adds the vectors 'l' and 'r' then stores the result in 'd'.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec2i			*vec2i_add(const t_vec2i *l, const t_vec2i *r, t_vec2i *d);
t_vec2f			*vec2f_add(const t_vec2f *l, const t_vec2f *r, t_vec2f *d);
t_vec2d			*vec2d_add(const t_vec2d *l, const t_vec2d *r, t_vec2d *d);

/*
** vec2*_sub: substracts the vector 'r' to 'l' then stores the result in 'd'.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec2i			*vec2i_sub(const t_vec2i *l, const t_vec2i *r, t_vec2i *d);
t_vec2f			*vec2f_sub(const t_vec2f *l, const t_vec2f *r, t_vec2f *d);
t_vec2d			*vec2d_sub(const t_vec2d *l, const t_vec2d *r, t_vec2d *d);

/*
** vec2*_mul: multiplies the vectors 'l' and 'r' then stores the result in 'd'.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec2i			*vec2i_mul(const t_vec2i *l, int r, t_vec2i *d);
t_vec2f			*vec2f_mul(const t_vec2f *l, float r, t_vec2f *d);
t_vec2d			*vec2d_mul(const t_vec2d *l, double r, t_vec2d *d);

/*
** vec2*_div: divides the vector 'l' with 'r' then stores the result in 'd'.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec2i			*vec2i_div(const t_vec2i *l, int r, t_vec2i *d);
t_vec2f			*vec2f_div(const t_vec2f *l, float r, t_vec2f *d);
t_vec2d			*vec2d_div(const t_vec2d *l, double r, t_vec2d *d);

/*
** vec2*_norm: calculates the norm (length) of a given vector.
*/
float			vec2i_norm(const t_vec2i *vec);
float			vec2f_norm(const t_vec2f *vec);
double			vec2d_norm(const t_vec2d *vec);

/*
** vec2*_normalize: normalizes the vector 'src' and stores the result into dst.
**
** The vec2i version will store its result into a vec2f instead of a vec2i.
**
** returns: the 'd' vector to allow chaining.
*/
t_vec2f			*vec2i_normalize(const t_vec2i *src, t_vec2f *dst);
t_vec2f			*vec2f_normalize(const t_vec2f *src, t_vec2f *dst);
t_vec2d			*vec2d_normalize(const t_vec2d *src, t_vec2d *dst);

/*
** vec2*_dot_product: calculates the dot product of the vectors r and l.
*/
float			vec2i_dot_product(const t_vec2i *r, const t_vec2i *l);
float			vec2f_dot_product(const t_vec2f *r, const t_vec2f *l);
double			vec2d_dot_product(const t_vec2d *r, const t_vec2d *l);

#endif
