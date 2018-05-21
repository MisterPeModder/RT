/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_internal.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 14:26:27 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/27 13:57:56 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_INTERNAL_H
# define ARGS_INTERNAL_H

# include "libft_base/list.h"
# include "args_defs.h"

/*
** Argument Parser internal functions:
** These functions below are NOT recomended for use in your program,
** => use them at your own peril.
*/

# define AERR "\033[1;31merror: \033[0m"

int					parse_option(t_arglst *arg, const char *curr);
int					parse_param(t_arglst *arg, char **av, int ac, int *i);
int					make_default_args(t_args *args, t_list **lst);
t_arglst			*get_arg(t_args *args, t_argtype type, const char *name);
char				*get_default_arg_err(int error, const char *detail);
void				arg_release(char **val);
t_arglst			*new_arg(t_argtype type, t_args *args, const char *name);

#endif
