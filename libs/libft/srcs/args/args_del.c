/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:32:00 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/24 14:11:51 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/stringft.h"
#include "libft_args/args.h"

void				arg_release(char **val)
{
	if (*val)
		free(*val);
	*val = NULL;
}

static void			release_argv(t_argtype type, t_argv *argv)
{
	size_t			i;

	if (type == DEFAULT)
	{
		i = 0;
		while (i < argv->d.argc)
		{
			free(argv->d.argv[i]);
			++i;
		}
		free(argv->d.argv);
	}
	else if (type == OPTION)
	{
		arg_release(&(argv->o.options_l));
		arg_release(&(argv->o.options_v));
	}
	else if (type == PARAMETER)
	{
		arg_release(&argv->l.name);
		if (argv->l.values)
			ft_strtabdel(&argv->l.values);
	}
}

static void			release_arglst(t_arglst **lst)
{
	t_arglst		*arg;
	t_arglst		*tmp;

	if (!*lst)
		return ;
	arg = *lst;
	while (arg)
	{
		release_argv(arg->type, &arg->argv);
		tmp = arg->next;
		free(arg);
		arg = tmp;
	}
	*lst = NULL;
}

void				free_args(t_args **args)
{
	release_arglst(&(*args)->arglst);
	arg_release(&(*args)->errinfo);
	arg_release(&(*args)->usage);
	free(*args);
	*args = NULL;
}
