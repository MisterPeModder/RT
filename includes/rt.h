/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:42:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/29 18:12:52 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "image.h"
# include "objects.h"
# include "scene.h"
# include "sdl_defs.h"
# include "ocl_data.h"
# include "ocl_types.h"
# include "controller.h"

/*
** SF*: State Flags.
*/

/*
** SF_SHOULD_UPDATE: This bit is set when the frame needs to be recomputed.
*/
# define SF_SHOULD_UPDATE 1

/*
** SF_NO_NEGATIVE: This bit is set when there is no negative object
**                 currently loaded in the scene, used for optimization.
*/
# define SF_NO_NEGATIVE 2

/*
** t_rt: The central structure.
*/
typedef struct		s_rt
{
	t_scene			scene;
	t_sdl_ctx		sdl;
	t_ocl			ocl;
	SDL_Surface		*frame;
	t_mem_info		mem_info;
	t_mv_state		mvs;
	int				state_flags;
	float			last_time;
	t_controller	controller;
}					t_rt;

int					core_init(t_rt *core, unsigned int w, unsigned int h);

/*
** event_loop: Triggers the main event loop. reminiscent of mlx_loop()
*/
void				event_loop(t_rt *core);

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
int					bool_from_json(const t_json_value *val, int *b);
int					int_from_json(const t_json_value *val, int *i);

/*
** ret_free: Frees the given pointer and returns NULL
*/
void				*ret_free(void *obj);
int					rel_error(const char *msg, t_json_object **obj);

/*
** make_cam: Handles the parsing of the camera properties.
*/
int					make_cam(t_cam *cam, const t_json_object *data);

cl_int				render_frame(t_rt *core, t_timer *t);
int					print_frame(t_rt *core, t_timer *t);

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
float				vec3cl_dot_product(const t_clfloat3 *r,
		const t_clfloat3 *l);

float				lin_inter(float x, float y, float s);
float				smooth_inter(float x, float y, float s);
int					noise2(int x, int y);
float				noise2d(float x, float y);
float				perlin2d(float x, float y, float freq, int depth);

int					parse_args(int ac, char **av, char **options_path);

t_json_value		*json_file_read(const char *path);

# define DEFAULT_OPTIONS "./options.json"

int					options_parse(t_rt *core, const char *path);

#endif
