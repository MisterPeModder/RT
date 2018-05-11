/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:29:09 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/11 17:55:48 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <json.h>
# include <stdint.h>
# include <libft_math/vec3.h>

typedef uint8_t		t_color[3];

typedef enum		e_obj_type
{
	OBJ_SPHERE = 1,
	OBJ_PLANE
}					t_obj_type;

typedef union		u_properties
{
	struct {
		float		radius;
	}				sphere;
	struct {
		t_vec3f		normal;
	}				plane;
}					t_properties;

struct s_object;

typedef struct		s_rt_result
{
	struct s_object	*obj;
	t_vec3f			pos;
	t_vec3f			normal;
	float			dist;
}					t_rt_result;

typedef struct		s_object
{
	t_obj_type		type;
	t_vec3f			pos;
	t_vec3f			angle;
	t_color			color;
	float			brightness;
	t_properties	props;
	void			(*release)(struct s_object *);
	float			(*intersect)(struct s_object *, t_vec3f *, t_vec3f *);
	void			(*normal)(struct s_object *, t_rt_result *r);
}					t_object;

int					sphere_init(t_object *object, const t_json_object *data);
float				sphere_intersect(t_object *o, t_vec3f *origin, t_vec3f *u);
void				sphere_normal(t_object *o, t_rt_result *r);

int					plane_init(t_object *object, const t_json_object *data);
float				plane_intersect(t_object *o, t_vec3f *origin, t_vec3f *u);
void				plane_normal(t_object *o, t_rt_result *r);

#endif
