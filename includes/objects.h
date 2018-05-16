/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:29:09 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/16 14:55:11 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <json.h>
# include <stdint.h>
# include <libft_math/vec3.h>

/*
** t_color: The color type.
**          Entries are stored in the RGB format.
*/
typedef uint8_t		t_color[3];

/*
** t_obj_type: Contains each type of object currently available.
*/
typedef enum		e_obj_type
{
	OBJ_SPHERE = 1,
	OBJ_PLANE,
	OBJ_CONE,
	OBJ_CYLINDER
}					t_obj_type;

/*
** t_properties: Contains the special properties of objects.
*/
typedef union		u_properties
{
	struct {
		float		radius;
	}				sphere;
	struct {
		t_vec3f		normal;
	}				plane;
	struct {
		t_vec3f		axis;
		float		opening_angle;
	}				cone;
	struct {
		t_vec3f		axis;
		float		radius;
	}				cylinder;
}					t_properties;

struct s_object;

/*
** t_rt_result: Stands for: RayTraceResult. Stores the infos about a ray.
**
** -obj: the touched object.
** -pos: where the intersection is located.
** -normal: normal vector of the surface at the intersection point.
** -dist: distance of the intersection from the ray's origin.
*/
typedef struct		s_rt_result
{
	struct s_object	*obj;
	t_vec3f			pos;
	t_vec3f			normal;
	float			dist;
}					t_rt_result;

/*
** t_object: Stores all the info about an object instance.
**
** -type: its type, see the t_obj_type enum for more info.
** -pos: where the object is located.
** -angle: its orientation.
** -brightness: self explanatory.
** -props: the properties of this object.
** -release: a function that frees memory that has been allocated by the object.
**           may be NULL.
** -intersect: a function that computes the intersection between a ray
**             and this object.
** -normal: a function that computes the normal vector at the given position.
*/
typedef struct		s_object
{
	t_obj_type		type;
	t_vec3f			pos;
	t_vec3f			angle;
	t_vec3f			color;
	float			brightness;
	t_properties	props;
	void			(*release)(struct s_object *);
	float			(*intersect)(struct s_object *, t_vec3f *, t_vec3f *);
	void			(*normal)(struct s_object *, t_rt_result *r);
}					t_object;

/*
** OBJECT FUNCTIONS:
**
** each object must declare an initialization function, an intersect function,
** a notmal function and optionnaly a release function.
*/
int					sphere_init(t_object *object, const t_json_object *data);
float				sphere_intersect(t_object *o, t_vec3f *origin, t_vec3f *u);
void				sphere_normal(t_object *o, t_rt_result *r);

int					plane_init(t_object *object, const t_json_object *data);
float				plane_intersect(t_object *o, t_vec3f *origin, t_vec3f *u);
void				plane_normal(t_object *o, t_rt_result *r);

int					cone_init(t_object *object, const t_json_object *data);
float				cone_intersect(t_object *o, t_vec3f *origin, t_vec3f *u);
void				cone_normal(t_object *o, t_rt_result *r);

int					cylinder_init(t_object *object, const t_json_object *data);
float				cylinder_intersect(t_object *o, t_vec3f *origin,
		t_vec3f *u);
void				cylinder_normal(t_object *o, t_rt_result *r);
#endif
