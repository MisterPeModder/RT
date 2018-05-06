/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 17:42:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/06 23:15:31 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include <libft_math/vec3.h>
# include <json.h>
# include <stdint.h>

typedef struct		s_color
{
	uint8_t			rgb[3];
}					t_color;

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

t_img				*img_make(unsigned int w, unsigned int h);
void				img_release(t_img **img);
void				img_output(t_img *img);

float				to_radians(float deg);
float				to_degrees(float rad);

int					float_from_json(const t_json_value *val, float *f);
int					vec3f_from_json(const t_json_value *arr, t_vec3f *vec);
void				*ret_free(void *obj);

t_json_value		*scene_read(const char *path);

int					make_cam(t_cam *cam, const t_json_object *data);

#endif
