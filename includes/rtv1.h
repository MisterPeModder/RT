/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:42:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 18:42:50 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "objects.h"

typedef struct		s_img
{
	unsigned int	w;
	unsigned int	h;
	t_color			**data;
}					t_img;

typedef struct		s_cam
{
	t_vec3f			pos;
	t_vec3f			angle;
	float			fov;
}					t_cam;

typedef struct		s_scene
{
	t_cam			cam;
	t_object		*objs;
	t_vec3f			*lights;
	size_t			objs_num;
	size_t			lights_num;
	t_color			bg_color;
}					t_scene;

int					exit_rtv1(t_img *img);

t_img				*img_make(unsigned int w, unsigned int h);
void				img_release(t_img **img);

float				to_radians(float deg);
float				to_degrees(float rad);

int					float_from_json(const t_json_value *val, float *f);
int					vec3f_from_json(const t_json_value *arr, t_vec3f *vec);
int					color_from_json(const t_json_value *arr, t_color color);
int					angle_from_json(const t_json_value *arr, t_vec3f *vec);

void				*ret_free(void *obj);

void				color_fill(t_color color, uint8_t r, uint8_t g, uint8_t b);
void				color_brightness(t_color color, t_color src, float b);

int					scene_parse(t_scene *scene, const char *path);
int					scene_lights(t_scene *scene, const t_json_array *data);

int					make_cam(t_cam *cam, const t_json_object *data);

int					obj_make(t_object *object, const t_json_object *data);
int					obj_release(t_object *obj);
int					objs_release(t_object *objs, size_t num);

t_hitlst			*hitlstnew(t_object *obj, float dist, t_vec3f *pos,
		t_vec3f *normal);
void				hitlstdel(t_hitlst *lst);
t_hitlst			*hitlstjoin(t_hitlst *big, t_hitlst *small);

void				render_frame(t_scene *scene, t_img *img);

t_vec3f				*rotate_x(const t_vec3f *src, t_vec3f *dst, float rx);
t_vec3f				*rotate_y(const t_vec3f *src, t_vec3f *dst, float ry);
t_vec3f				*rotate_z(const t_vec3f *src, t_vec3f *dst, float rz);

# define USE_MLX 1

# define X11_DESTROYNOTIFY 17
# define X11_STRUCTURENOTIFYMASK (1L << 17)

void				img_ppm_output(t_img *img);
void				img_mlx_output(t_img *img);

#endif
