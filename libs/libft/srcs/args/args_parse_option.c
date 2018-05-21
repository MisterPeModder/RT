/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse_option.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:50:42 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/24 14:13:24 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/character.h"
#include "libft_base/stringft.h"
#include "libft_args/args.h"

static int			check_multiple_options(t_args *args, const char *str)
{
	int				i;
	int				j;
	char			err[3];

	i = -1;
	err[0] = '-';
	err[2] = '\0';
	while (str[++i])
	{
		j = i;
		while (str[++j])
			if (str[i] == str[j])
			{
				err[1] = str[i];
				return (set_arg_error(args, ARG_DEF_TWICE, err));
			}
	}
	return (clear_arg_errors(args));
}

static void			join_options(t_arglst *arg, char *sub)
{
	if (!arg->argv.o.options_v)
		arg->argv.o.options_v = sub;
	else
		arg->argv.o.options_v = ft_strconcat(arg->argv.o.options_v, sub, 3);
}

int					parse_option(t_arglst *arg, const char *curr)
{
	size_t				size;

	if (!arg)
		return (set_arg_error(arg->args, ARG_UNKNOWN_OPTION, curr));
	if (!curr[1] || ft_isspace(curr[1]))
		return (set_arg_error(arg->args, ARG_UNSPECIFIED, NULL));
	size = 0;
	while (curr[size + 1] && !ft_isspace(curr[size + 1]))
		++size;
	join_options(arg, ft_strsub(curr, 1, size));
	return (check_multiple_options(arg->args, arg->argv.o.options_v));
}
