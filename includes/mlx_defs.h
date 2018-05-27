/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_defs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:14:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 14:16:20 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_DEFS_H
# define MLX_DEFS_H

# include <mlx.h>

/*
** t_mlx_ctx: contains info about the mlx window.
*/
typedef struct		s_mlx_ctx
{
	void			*mlx_ptr;
	void			*win_ptr;
	unsigned int	win_width;
	unsigned int	win_height;
}					t_mlx_ctx;

/*
** == EVENTS ==
*/

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
# ifdef X11_MLX
#  define ESC_KEY 65307
# else
#  define ESC_KEY 53
# endif

int					on_key_released(int key, void *core);
int					on_window_closing(void *core);

#endif
