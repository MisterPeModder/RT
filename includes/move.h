/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 18:23:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/31 19:12:28 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include <math.h>
# include "rt.h"
# include "timer.h"

# define MOVE_INCREMENT .5f
# define ROTATE_INCREMENT (.02f * M_PI)

void				move_cam(t_rt *core, int key, t_timer *time);
void				rotate_cam(t_rt *core, int key, t_timer *time);

#endif
