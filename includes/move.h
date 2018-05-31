/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 18:23:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 16:07:37 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MOVE_H
# define MOVE_H

# include "rt.h"

# define MOVE_INCREMENT .5f
# define ROTATE_INCREMENT .1f

void				move_cam(t_rt *core, int key);
void				rotate_cam(t_rt *core, int key);

#endif
