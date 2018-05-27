/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:29:09 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/26 17:52:03 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <json.h>
# include <stdint.h>
# include <libft_math/vec3.h>

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
** OBJ_TYPES_COUNT: defines the number of object types
*/
# define OBJ_TYPES_COUNT 4

/*
** OBJ_NAME_SIZE: Maximum size of objects name
*/
# define OBJ_NAME_SIZE 32

struct s_object;

/*
** t_obj_class: Represents an object type.
**
** -constuct: a function that initializes values for the object.
** -intersect: a function that computes the intersection between a ray
**             and this object.
** -normal: a function that computes the normal vector at the given position.
*/
typedef struct		s_obj_class
{
	char			name[OBJ_NAME_SIZE];
	int				(*construct)(struct s_object *, const t_json_object *);
	float			(*intersect)(struct s_object *, t_vec3f *, t_vec3f *);
	void			(*normal)(struct s_object *, t_rt_result *r);
}					t_obj_class;

/*
** t_properties: Contains the special properties of objects.
*/
typedef union		u_properties
{
	struct {
		float		radius;
	}				sphere;
	struct {
		float		opening_angle;
	}				cone;
	struct {
		float		radius;
	}				cylinder;
}					t_properties;

/*
** t_object: Stores all the info about an object instance.
**
** -pos: where the object is located.
** -facing: its orientation.
** -props: the properties of this object.
** -type: its class, see the t_obj_class struct for more info.
*/
typedef struct		s_object
{
	t_vec3f			pos;
	t_vec3f			facing;
	t_vec3f			color;
	t_properties	props;
	t_obj_class		*type;
}					t_object;

/*
** add_object_classes: Initializes the object class index.
*/
void				add_object_classes(t_obj_class *classes);

/*
** OBJECT FUNCTIONS:
**
** each object must declare an initialization function, an intersect function,
** a notmal function and optionnaly a release function.
*/
int					sphere_init(t_object *object, const t_json_object *data);
float				sphere_intersect(t_object *o, t_vec3f *origin, t_vec3f *u);
void				sphere_normal(t_object *o, t_rt_result *r);

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
