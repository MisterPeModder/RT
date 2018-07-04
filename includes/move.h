/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 18:23:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/07/04 01:40:24 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include <SDL_keyboard.h>
# include <math.h>
# include "timer.h"

# define MOVE_INCREMENT .5f
# define ROTATE_INCREMENT (.02f * M_PI)

struct s_rt;

void				move_cam(struct s_rt *core, int key, t_timer *time);
void				rotate_cam(struct s_rt *core, int key, t_timer *time);

#endif
