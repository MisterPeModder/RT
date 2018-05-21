/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:07:52 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/24 14:11:39 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/stringft.h"
#include "libft_args/args.h"

t_arglst			*new_arg(t_argtype type, t_args *args, const char *name)
{
	t_arglst		*arg;

	if ((arg = get_arg(args, type, name)))
		return (arg);
	if (!(arg = (t_arglst *)malloc(sizeof(t_arglst))))
		return (NULL);
	arg->type = type;
	arg->next = NULL;
	if (args->arglst)
		arg->next = args->arglst;
	args->arglst = arg;
	arg->args = args;
	return (arg);
}

int					add_arg_options(t_args *args, const char *options)
{
	t_arglst		*curr;

	if (!args || !options || !*options)
		return (set_arg_error(args, ARG_UNKNOWN_ERR, NULL));
	if (!(curr = new_arg(OPTION, args, NULL)))
		return (set_arg_error(args, ARG_MEM_ERROR, NULL));
	curr->argv.o.options_l = ft_strdup(options);
	curr->argv.o.options_v = NULL;
	return (clear_arg_errors(args));
}

int					add_arg_param(t_args *args, const char *name,
		size_t size, t_size_policy policy)
{
	t_arglst		*curr;

	if (!args || !name || !*name)
		return (set_arg_error(args, ARG_UNKNOWN_ERR, NULL));
	if (!(curr = new_arg(PARAMETER, args, NULL)))
		return (set_arg_error(args, ARG_MEM_ERROR, NULL));
	curr->argv.l.name = ft_strdup(name);
	curr->argv.l.defined = 0;
	curr->argv.l.size = size;
	curr->argv.l.policy = policy;
	curr->argv.l.values = NULL;
	curr->argv.l.validator = NULL;
	return (clear_arg_errors(args));
}
