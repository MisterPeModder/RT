/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controller.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 07:59:37 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/08 20:41:38 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONTROLLER_H
# define CONTROLLER_H

# include <json.h>
# include <libft_containers/hashmap.h>
# include <SDL_gamecontroller.h>

typedef struct			s_scheme
{
	const char			*name;
	int					*buttons_ids;
	int					*bkeys_ids;
	size_t				buttons_len;
	int					*axis_ids;
	int					*akeys_ids;
	size_t				axis_len;
}						t_scheme;

typedef struct			s_controller
{
	SDL_GameController	*controller;
	SDL_GameController	*extra;
	t_scheme			*current_scheme;
	t_scheme			*schemes;
	t_hashmap			*con_schemes;
}						t_controller;

struct s_rt;

int						add_sdl_mappings(const t_json_array *mappings);
void					controller_update(t_controller *data);

void					on_controller_button_pressed(void *event,
		struct s_rt *core);
void					on_controller_button_released(void *event,
		struct s_rt *core);
void					on_controller_connect(Sint32 id,
		struct s_rt *core);
void					on_controller_disconnect(Sint32 id,
		struct s_rt *core);
void					on_controller_axis_motion(void *event,
		struct s_rt *core);

#endif
