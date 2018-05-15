/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_defs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:14:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/15 15:34:12 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_DEFS_H
# define MLX_DEFS_H

/*
** Event ids
*/
# define DESTROYNOTIFY 17

/*
** Event masks
*/
# define STRUCTURENOTIFYMASK (1L << 17)

/*
** Key codes, these are the key codes for macOS version of the mlx.
*/
# define ESC_KEY 53

/*
** == EVENTS ==
*/
int					on_key_released(int key, void *img);
int					on_window_closing(void *img);

#endif
