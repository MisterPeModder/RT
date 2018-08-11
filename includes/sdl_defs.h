/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_defs.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 14:14:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/11 16:28:40 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_DEFS_H
# define SDL_DEFS_H

# include <SDL_video.h>
# include <SDL_endian.h>
# include "timer.h"

# define MAX_FONT_NAME 256

/*
** t_sdl_ctx: contains info about the sdl window.
*/
typedef struct		s_sdl_ctx
{
	SDL_Window		*win;
	SDL_Surface		*screen;
	SDL_Surface		*ui;
	unsigned int	win_width;
	unsigned int	win_height;
	unsigned int	frame_width;
	unsigned int	frame_height;
	int				con_state;
	void			*font;
	char			font_name[MAX_FONT_NAME];
	int				show_ui;
}					t_sdl_ctx;

# if SDL_BYTEORDER == SDL_BIG_ENDIAN
#  define IMAGE_FORMAT SDL_PIXELFORMAT_ARGB32
# else
#  define IMAGE_FORMAT SDL_PIXELFORMAT_BGRA32
# endif

# define MAX_KEYS 8
# define TXT_BOX_PADDING 10

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

struct s_rt;

/*
** == UI ==
*/

void				render_ui(struct s_rt *core, t_timer *t);
char				*display_fps(struct s_rt *core, t_timer *t, int last);
char				*display_depth(struct s_rt *core);
char				*display_sample(struct s_rt *core);
/*
** == EVENTS ==
*/

void				on_key_pressed(int key, struct s_rt *core);
void				on_key_released(int key, struct s_rt *core);
void				on_key_repeat(int key, t_timer *time, struct s_rt *core);
void				key_handling(int key, struct s_rt *core);
void				repeated_key_handling(int key, struct s_rt *core);
void				on_window_closing(struct s_rt *core);
void				exit_rt(struct s_rt *core);
void				on_tick(struct s_rt *core);
void				on_window_event(void *event, struct s_rt *core);
void				change_filter(int key, struct s_rt *core);

#endif
