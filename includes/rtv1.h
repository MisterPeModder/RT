/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:42:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/17 13:52:02 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "objects.h"

/*
** IMG_W, IMG_H: The image's width and height.
*/
# define IMG_W 1200
# define IMG_H 675

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
** t_light: Represents a light.
**
** -pos: its location
** -power: how bright it is
** -color: its color
*/
typedef struct		s_light
{
	t_vec3f			pos;
	float			power;
	t_vec3f			color;
}					t_light;

/*
** t_scene: A structure that stores all the information about the current scene.
**
** -cam: the camera structure (see above)
** -types: an array of object classes, containes the info about
**         the avalible object types.
** -lights: an array of vectors containing the lights' positions
** -objs_num: the number of object stored
** -lights_num: the number of lights stored
** -bg_color: the background color
*/
typedef struct		s_scene
{
	t_cam			cam;
	t_obj_class		types[OBJ_TYPES_COUNT];
	t_object		*objs;
	t_light			*lights;
	size_t			objs_num;
	size_t			lights_num;
	t_vec3f			bg_color;
}					t_scene;

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
int					color_from_json(const t_json_value *arr, t_vec3f *color);
int					angle_from_json(const t_json_value *arr, t_vec3f *vec);

/*
** ret_free: Frees the given pointer and returns NULL
*/
void				*ret_free(void *obj);
int					rel_error(const char *msg, t_json_object **obj);

/*
** color_fill: Sets the red, green and blue values of the passed t_color.
*/
void				color_fill(t_color color, uint8_t r, uint8_t g, uint8_t b);

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
** scene_parse: Parses the scene JSON file.
**
** -scene: the scene object
** -path: the file path
**
** returns: 1 if successful, 0 if not.
*/
int					scene_parse(t_scene *scene, const char *path);
int					scene_lights(t_scene *scene, const t_json_array *data);
void				scene_release(t_scene *scene);

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
