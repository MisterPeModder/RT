/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_defs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:14:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/31 19:44:24 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_DEFS_H
# define MLX_DEFS_H

# include <mlx.h>
# include "timer.h"

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

# define MAX_KEYS 8

typedef struct		s_key
{
	int				set;
	t_timer			time;
	int				code;
}					t_key;

typedef struct		s_mv_state
{
	t_key			keys[MAX_KEYS];
	float			move_speed;
	float			rotate_speed;
}					t_mv_state;

/*
** == EVENTS ==
*/

/*
** Event ids
*/
# define KEYPRESS 2
# define KEYRELEASE 3
# define DESTROYNOTIFY 17

/*
** Event masks
*/
# define KEYPRESSMASK (1L << 0)
# define KEYRELEASEMASK (1L << 1)
# define STRUCTURENOTIFYMASK (1L << 17)

/*
** Key codes, these are the key codes for macOS version of the mlx.
*/
# ifdef X11_MLX
#  define ESC_KEY 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define SHIFT_KEY 65505
#  define SPACE_KEY 32
# else
#  define ESC_KEY 53
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define SPACE_KEY 49
#  define SHIFT_KEY 257
#  define ARROW_UP_KEY 126
#  define ARROW_LEFT_KEY 123
#  define ARROW_DOWN_KEY 125
#  define ARROW_RIGHT_KEY 124
#  define PG_UP 116
#  define PG_DOWN 121
# endif

int					on_key_pressed(int key, void *core);
int					on_key_released(int key, void *core);
void				on_key_repeat(int key, t_timer *time, void *core);
int					on_window_closing(void *core);
int					on_tick(void *core);

#endif
