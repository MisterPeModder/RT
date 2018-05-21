/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 16:52:13 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/19 11:29:29 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft_base/stringft.h"
#include "libft_base/io.h"
#include "libft_args/args.h"

static char			*gda_err_helper(t_arg_error error, char *detail)
{
	char			*err;
	char			*tmp;

	err = NULL;
	if (error & ARG_EMPTY)
		err = ft_strdup(AERR "missing arguments.");
	else if (error & ARG_MEM_ERROR)
		err = ft_strdup(AERR "ran out of memory while parsing arguments.");
	else if (error & ARG_UNKNOWN_OPTION)
		err = ft_strconcat(AERR "illegal option: ", detail, 0);
	else if (error & ARG_UNKNOWN_PARAM)
		err = ft_strconcat(AERR "illegal parameter: ", detail, 0);
	else if (error & ARG_PARAM_VALUE)
		err = ft_strconcat(AERR "invalid value ", detail, 0);
	else if (error & ARG_DEF_TWICE)
	{
		tmp = ft_strconcat(AERR "argument \"", detail, 0);
		err = ft_strconcat(tmp, "\" is defined muliple times.", 1);
	}
	return (err);
}

char				*get_default_arg_err(int error, const char *detail)
{
	char			*err;

	if (error == ARG_VALID)
		return (NULL);
	if ((err = gda_err_helper((t_arg_error)error, (char *)detail)))
		return (err);
	else if (error & ARG_UNSPECIFIED)
		err = ft_strdup(AERR "unspecified argument.");
	else if (error & ARG_INVALID_SIZE)
		err = ft_strjoin(AERR "invalid number of arguments for parameter ",
				detail);
	else
		err = ft_strdup(AERR "unknown error");
	return (err);
}

void				put_arg_error(const char *prefix, const t_args *args)
{
	char			*ret;

	if (!args)
	{
		ft_putstr_fd(prefix, STDERR_FILENO);
		ft_putendl_fd(": failed to allocate arguments!", STDERR_FILENO);
		return ;
	}
	if (args->errcode == ARG_VALID)
		return ;
	if (args->err_to_str && (ret = (*args->err_to_str)(args->errcode,
					args->errinfo)))
	{
		ft_putstr_fd(prefix, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putendl_fd(ret, STDERR_FILENO);
		free(ret);
	}
	show_usage(args);
}

void				show_usage(const t_args *args)
{
	if (args && args->usage)
		ft_putendl_fd(args->usage, STDERR_FILENO);
}
