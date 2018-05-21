/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 14:52:30 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/24 14:12:35 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/stringft.h"
#include "libft_args/args.h"

t_args				*init_args(int mode,
		char *(*err)(int, const char *), const char *usage)
{
	t_args			*args;

	if (!(args = malloc(sizeof(t_args))))
		return (NULL);
	args->arglst = NULL;
	args->err_to_str = err ? err : &get_default_arg_err;
	args->mode = mode;
	args->errcode = ARG_VALID;
	args->errinfo = NULL;
	args->usage = usage ? ft_strdup(usage) : NULL;
	return (args);
}
