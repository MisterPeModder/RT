/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filters.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 00:56:27 by jhache            #+#    #+#             */
/*   Updated: 2018/08/21 19:38:34 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILTERS_H
# define FILTERS_H

# include "sdl_defs.h"
# include "move.h"

struct s_rt;

typedef enum		e_filter
{
	FILTER_NONE = SDLK_0,
	FILTER_RED = SDLK_1,
	FILTER_GREEN = SDLK_2,
	FILTER_BLUE = SDLK_3,
	FILTER_GREY = SDLK_4,
	FILTER_BLACK_WHITE = SDLK_5,
	FILTER_NEG = SDLK_6
}					t_filter;

void				apply_filter(struct s_rt *core);

#endif
