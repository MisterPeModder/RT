/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:42:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/12 15:03:59 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "objects.h"

/*
** t_img: The frame buffer
**
** -w: the image width
** -h: the image height
** -data: A bidimensional array of colors
*/
typedef struct		s_img
{
	unsigned int	w;
	unsigned int	h;
	t_color			**data;
}					t_img;

/*
** t_cam: The camera
**
** -pos: where the cam is located
** -angle: its angle
** -fov: the field of view
*/
typedef struct		s_cam
{
	t_vec3f			pos;
	t_vec3f			angle;
	float			fov;
}					t_cam;

/*
** t_scene: A structure that stores all the information about the current scene.
**
** -cam: the camera structure (see above)
** -lights: an array of vectors containing the lights' positions
** -objs_num: the number of object stored
** -lights_num: the number of lights stored
** -bg_color: the background color
*/
typedef struct		s_scene
{
	t_cam			cam;
	t_object		*objs;
	t_vec3f			*lights;
	size_t			objs_num;
	size_t			lights_num;
	t_color			bg_color;
}					t_scene;

/*
** exit_rtv1: Exits the program.
*/
int					exit_rtv1(t_img *img);

/*
** img_make: Allocates memory for image and initializes it.
**
** -w: image width
** -h: image height
**
** returns: the image.
*/
t_img				*img_make(unsigned int w, unsigned int h);

/*
** img_release: Frees the passed image.
*/
void				img_release(t_img **img);

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
int					color_from_json(const t_json_value *arr, t_color color);
int					angle_from_json(const t_json_value *arr, t_vec3f *vec);

/*
** ret_free: Frees the given pointer and returns NULL
*/
void				*ret_free(void *obj);

/*
** color_fill: Sets the red, green and blue values of the passed t_color.
*/
void				color_fill(t_color color, uint8_t r, uint8_t g, uint8_t b);

/*
** colorize: Adds the color 'src' to the color 'color'.
**
** -color: where the result is stored
** -src: the color to be added to 'color'
** -comp[2]: the diffuse and specular component
**	(between 0 and 1) of the computed color.
*/
void				colorize(t_color color, t_color src, float comp[2]);

/*
** scene_parse: Parses the scene JSON file.
**
** -scene: the scene object
** -path: the file path
**
** returns: 1 if successful, 0 if not.
*/
int					scene_parse(t_scene *scene, const char *path);
int					scene_lights(t_scene *scene, const t_json_array *data);

/*
** make_cam: Handles the parsing of the camera properties.
*/
int					make_cam(t_cam *cam, const t_json_object *data);

int					obj_make(t_object *object, const t_json_object *data);
int					obj_release(t_object *obj);
int					objs_release(t_object *objs, size_t num);

void				render_frame(t_scene *scene, t_img *img);

/*
** rotate_*: Rotates the vector 'vec' by the angle 'r'.
*/
t_vec3f				*rotate_x(t_vec3f *vec, float rx);
t_vec3f				*rotate_y(t_vec3f *vec, float ry);
t_vec3f				*rotate_z(t_vec3f *vec, float rz);

# define USE_MLX 1

# define X11_DESTROYNOTIFY 17
# define X11_STRUCTURENOTIFYMASK (1L << 17)

void				img_ppm_output(t_img *img);
void				img_mlx_output(t_img *img);

#endif
