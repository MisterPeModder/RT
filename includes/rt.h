/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:42:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/06 01:02:59 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "image.h"
# include "scene.h"
# include "sdl_defs.h"
# include "ocl_data.h"
# include "ocl_types.h"

/*
** t_rt: The central structure.
*/
typedef struct		s_rt
{
	t_scene			scene;
	t_sdl_ctx		sdl;
	t_ocl			ocl;
	SDL_Surface		*frame;
	t_mv_state		mvs;
	int				should_update;
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

/*
** vec3cl_fill: fills the openCL float3 vector with the given coordinates.
*/
t_clfloat3			*vec3cl_fill(t_clfloat3 *vec,
		t_clfloat x, t_clfloat y, t_clfloat z);
t_clfloat3			*vec3cl_add(t_clfloat3 *rhs, t_clfloat3 *lhs,
		t_clfloat3 *dst);

cl_float3			*rotate_x(cl_float3 *vec, t_clfloat rx);
cl_float3			*rotate_y(cl_float3 *vec, t_clfloat ry);
cl_float3			*rotate_z(cl_float3 *vec, t_clfloat rz);

#endif
