/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:42:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/16 11:51:45 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <stdio.h>
# include "image.h"
# include "scene.h"
# include "mlx_defs.h"
# include "ocl_data.h"
# include "ocl_types.h"

/*
** t_rt: The central structure.
*/
typedef struct		s_rt
{
	t_scene			scene;
	t_mlx_ctx		mlx;
	t_ocl			ocl;
	t_img			*frame;
	t_mv_state		mvs;
	int				should_update;
	float			last_time;
}					t_rt;

int					core_init(t_rt *core, unsigned int w, unsigned int h);

t_clfloat			to_radians(t_clfloat deg);
t_clfloat			to_degrees(t_clfloat rad);

/*
** *_from_json: Parses the given t_json_value
**
** stores the result in the second paremeter.
**
** returns: 1 if successful, 0 if not.
*/
int					float_from_json(const t_json_value *val, t_clfloat *f);
int					vec3f_from_json(const t_json_value *arr, cl_float3 *vec);
int					color_from_json(const t_json_value *arr, cl_float3 *color);
int					angle_from_json(const t_json_value *arr, cl_float3 *vec);
int					bool_from_json(const t_json_value *val, int *f);

/*
** ret_free: Frees the given pointer and returns NULL
*/
void				*ret_free(void *obj);
int					rel_error(const char *msg, t_json_object **obj);

/*
** make_cam: Handles the parsing of the camera properties.
*/
int					make_cam(t_cam *cam, const t_json_object *data);

int					obj_make(t_object *object, const t_json_object *data);
int					obj_release(t_object *obj);
int					objs_release(t_object *objs, size_t num);

cl_int				render_frame(t_rt *core);

void				img_ppm_output(t_img *img);
void				img_mlx_output(t_img *img);

/*
** vec3cl_fill: fills the openCL float3 vector with the given coordinates.
*/
t_clfloat3			*vec3cl_fill(t_clfloat3 *vec,
		t_clfloat x, t_clfloat y, t_clfloat z);
t_clfloat3			*vec3cl_add(t_clfloat3 *rhs, t_clfloat3 *lhs,
		t_clfloat3 *dst);
t_clfloat3			*vec3cl_cross(t_clfloat3 *v1, t_clfloat3 *v2,
		t_clfloat3 *dst);
t_clfloat3			*vec3cl_mul(t_clfloat3 *v, float a, t_clfloat3 *dst);
t_clfloat3			*vec3cl_sub(t_clfloat3 *v1, t_clfloat3 *v2, t_clfloat3 *d);
t_clfloat3			*vec3cl_neg(t_clfloat3 *v, t_clfloat3 *d);
t_clfloat3			*vec3cl_normalize(t_clfloat3 *v, t_clfloat3 *d);

cl_float3			*rotate_x(cl_float3 *vec, t_clfloat rx);
cl_float3			*rotate_y(cl_float3 *vec, t_clfloat ry);
cl_float3			*rotate_z(cl_float3 *vec, t_clfloat rz);


float 			lin_inter(float x, float y, float s);
float 			smooth_inter(float x, float y, float s);
int				noise2(int x, int y);
float			noise2d(float x, float y);
float			perlin2d(float x, float y, float freq, int depth);

#endif
