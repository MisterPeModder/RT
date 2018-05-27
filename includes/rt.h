/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:42:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 14:59:58 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "image.h"
# include "scene.h"
# include "mlx_defs.h"

/*
** t_rt: The central structure.
*/
typedef struct		s_rt
{
	t_scene			scene;
	t_mlx_ctx		mlx;
	t_img			*frame;
	int				should_update;
}					t_rt;

int					core_init(t_rt *core, unsigned int w, unsigned int h);

float				to_radians(float deg);
float				to_degrees(float rad);

/*
** *_from_json: Parses the given t_json_value
**
** stores the result in the second paremeter.
**
** returns: 1 if successful, 0 if not.
*/
int					float_from_json(const t_json_value *val, float *f);
int					vec3f_from_json(const t_json_value *arr, t_vec3f *vec);
int					color_from_json(const t_json_value *arr, t_vec3f *color);
int					angle_from_json(const t_json_value *arr, t_vec3f *vec);

/*
** ret_free: Frees the given pointer and returns NULL
*/
void				*ret_free(void *obj);
int					rel_error(const char *msg, t_json_object **obj);

/*
** compute_color: Compute the Diffuse and the Specular components of the color.
**         Colorize is the function which will
**         add those components into one color.
** -light: the light's data structure we are using for computing the color.
** -lvec: a vector which is going from the intersection point
**        to the light coord.
** -r: the primary ray's raytrace result.
** -c: where the color of the pixel will be stored.
*/
void				colorize(t_light light, t_vec3f lvec, t_rt_result *r,
		t_vec3f *c);

/*
** make_cam: Handles the parsing of the camera properties.
*/
int					make_cam(t_cam *cam, const t_json_object *data);

int					obj_make(t_object *object, t_obj_class *types,
		const t_json_object *data);

void				render_frame(t_scene *scene, t_img *img);

/*
** rotate_*: Rotates the vector 'vec' by the angle 'r'.
*/
t_vec3f				*rotate_x(t_vec3f *vec, float rx);
t_vec3f				*rotate_y(t_vec3f *vec, float ry);
t_vec3f				*rotate_z(t_vec3f *vec, float rz);

/*
** read_args: Parses argv.
**
** returns: -1 if an error occured, 0 if the program should output to
**          a ppm image or 1 if it should display a window.
*/
int					read_args(int ac, char **av);

void				img_ppm_output(t_img *img);
void				img_mlx_output(t_img *img);

#endif
