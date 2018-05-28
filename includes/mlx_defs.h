/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_defs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:14:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/27 19:49:37 by yguaye           ###   ########.fr       */
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
# define KEYPRESS 2
# define DESTROYNOTIFY 17

/*
** Event masks
*/
# define KEYPRESSMASK (1L << 0)
# define STRUCTURENOTIFYMASK (1L << 17)

/*
** Key codes, these are the key codes for macOS version of the mlx.
*/
# ifdef X11_MLX
#  define ESC_KEY 65307
# else
#  define ESC_KEY 53
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define SPACE_KEY 49
#  define SHIFT_KEY 257
# endif

int					on_key_pressed(int key, void *core);
int					on_window_closing(void *core);
int					on_tick(void *core);

#endif
