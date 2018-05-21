/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_get.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/11 10:59:17 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/27 14:33:36 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/stringft.h"
#include "libft_args/args.h"

static int			has_chr(char *str, char chr)
{
	if (str == NULL)
		return (0);
	return (ft_strchr(str, chr) != NULL);
}

int					has_arg(const t_args *args, char *name,
		t_argtype type)
{
	t_arglst		*curr;

	curr = args->arglst;
	while (curr)
	{
		if (type == curr->type && ((type == OPTION && name &&
						has_chr(curr->argv.o.options_v, *name))
					|| (type == PARAMETER && curr->argv.l.name && name &&
						ft_strequ(curr->argv.l.name, name) &&
						curr->argv.l.defined) || type == DEFAULT))
			return (1);
		curr = curr->next;
	}
	return (0);
}

int					is_arg_listed(const t_args *args, const char *name,
		t_argtype type)
{
	t_arglst		*curr;

	curr = args->arglst;
	while (name && curr)
	{
		if (type == curr->type && ((curr->type == OPTION &&
						has_chr(curr->argv.o.options_l, *name))
					|| (curr->type == PARAMETER &&
						curr->argv.l.name &&
						ft_strequ(curr->argv.l.name, name))))
			return (1);
		curr = curr->next;
	}
	return (0);
}

t_arglst			*get_arg(t_args *args, t_argtype type, const char *name)
{
	t_arglst		*curr;

	curr = args->arglst;
	while (curr)
	{
		if (curr->type == type && (type != PARAMETER || (name &&
						ft_strequ(curr->argv.l.name, name))))
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

t_argv_plst			*get_pargv(t_args *args, const char *name)
{
	t_arglst		*res;

	res = get_arg(args, PARAMETER, name);
	return (res && res->argv.l.defined ? &res->argv.l : NULL);
}
