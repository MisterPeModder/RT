/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 13:29:09 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/07 18:41:16 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

# include <stdint.h>
# include <libft_math/vec3.h>

typedef uint8_t		t_color[3];

typedef enum		e_obj_type
{
	OBJ_SPHERE = 1
}					t_obj_type;

typedef union		u_properties
{
	struct {
		float		radius;
	}				sphere;
}					t_properties;

typedef struct		s_object
{
	t_obj_type		type;
	t_vec3f			pos;
	t_vec3f			angle;
	t_color			color;
	t_properties	props;
	void			(*release)(struct s_object *);
}					t_object;

#endif
