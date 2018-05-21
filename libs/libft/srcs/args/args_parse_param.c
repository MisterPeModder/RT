/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse_param.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 14:51:14 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/28 15:39:52 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/stringft.h"
#include "libft_base/memory.h"
#include "libft_args/args.h"

static int			copy_param_args(t_arglst *arg, char **av, int *i, int len)
{
	int				j;

	j = 0;
	while (j < len)
	{
		if (!(arg->argv.l.values[j] = (char *)malloc(sizeof(char *) *
						ft_strlen(av[*i + 1]))))
		{
			while (--j >= 0)
				free(arg->argv.l.values[j]);
			return (set_arg_error(arg->args, ARG_MEM_ERROR, NULL));
		}
		ft_strcpy(arg->argv.l.values[j], av[*i + 1]);
		++j;
		++*i;
	}
	return (clear_arg_errors(arg->args));
}

int					parse_param(t_arglst *arg, char **av, int ac, int *i)
{
	size_t			len;

	if (!arg)
		return (-2);
	len = 0;
	while ((int)len + *i + 1 < ac && av[(int)len + *i + 1][0] != '-')
		++len;
	if (len > arg->argv.l.size)
		len = arg->argv.l.policy == SIZEP_MIN ? len : arg->argv.l.size;
	if ((arg->argv.l.policy == SIZEP_MIN && arg->argv.l.size > len) ||
			(arg->argv.l.policy == SIZEP_FORCE && arg->argv.l.size != len) ||
			(arg->argv.l.policy == SIZEP_MAX && arg->argv.l.size < len))
		return (set_arg_error(arg->args, ARG_INVALID_SIZE, av[*i]));
	arg->argv.l.defined = 1;
	if (len == 0)
		return (clear_arg_errors(arg->args));
	if (!(arg->argv.l.values = (char **)ft_memalloc(sizeof(char *) *
					(len + 1))))
		return (set_arg_error(arg->args, ARG_MEM_ERROR, NULL));
	return (copy_param_args(arg, av, i, (int)len));
}
