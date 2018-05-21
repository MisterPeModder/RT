/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/10 15:44:16 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/28 15:39:30 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/stringft.h"
#include "libft_base/list.h"
#include "libft_args/args.h"

static int			validate_args(t_args *args)
{
	t_arglst		*curr;
	int				i;
	char			option[2];

	curr = args->arglst;
	option[1] = 0;
	while (curr)
	{
		i = -1;
		while (curr->type == OPTION && curr->argv.o.options_v &&
				curr->argv.o.options_v[++i])
			if (curr->argv.o.options_v[i] != '-' &&
					!is_arg_listed(args, curr->argv.o.options_v + i, OPTION))
			{
				option[0] = curr->argv.o.options_v[i];
				return (set_arg_error(args, ARG_UNKNOWN_OPTION, option));
			}
		if (curr->type == PARAMETER && !is_arg_listed(args, curr->argv.l.name,
					PARAMETER))
			return (set_arg_error(args, ARG_UNKNOWN_PARAM, curr->argv.l.name));
		curr = curr->next;
	}
	return (clear_arg_errors(args));
}

static char			*get_param_basename(const char *str, int simple)
{
	unsigned int	offset;
	size_t			slen;
	size_t			len;

	slen = ft_strlen(str);
	if (simple ? slen <= 1 : slen <= 2)
		return (ft_strdup(""));
	offset = str[1] == '-' ? 2 : 1;
	len = 0;
	while (str[len + offset] && str[len + offset] != '=')
		++len;
	return (ft_strsub(str, offset, len));
}

static int			parse_args_param(t_args *args, int ac, char **av, int *i)
{
	char			*tmp;
	int				ret;

	ret = 0;
	if (!(tmp = get_param_basename(av[*i], args->mode & ARG_MSIMPLE)) || !*tmp)
	{
		set_arg_error(args, ARG_UNSPECIFIED, tmp);
		ret = -1;
	}
	else if (args->mode & ARG_MSINGLE_PARAMS && has_arg(args, tmp, PARAMETER))
	{
		set_arg_error(args, ARG_DEF_TWICE, tmp);
		ret = -1;
	}
	else
		ret = parse_param(get_arg(args, PARAMETER, tmp), av, ac, i);
	if (ret == -2)
		set_arg_error(args, ARG_UNKNOWN_PARAM, tmp);
	ft_strdel(&tmp);
	return (ret);
}

static void			parse_add2lst(t_list **lst, char *str)
{
	t_list			*nl;

	if (!(nl = ft_lstnew(NULL, 0)))
		return ;
	nl->content = (void *)ft_strdup(str);
	ft_lstadd(lst, nl);
}

int					parse_args(t_args *args, int ac, char **av)
{
	int				i;
	int				ret;
	char			*str;
	int				simple;
	t_list			*lst;

	if (ac <= (i = 0) + 1)
		return (set_arg_error(args, ARG_EMPTY, NULL));
	lst = NULL;
	simple = args->mode & ARG_MSIMPLE;
	while (++i < ac)
	{
		str = av[i];
		ret = 0;
		if (!simple && str[0] == '-' && (str[1] != '-' ||
					(args->mode & ARG_MENABLE_SEP && str[1] == '-' && !str[2])))
			ret = parse_option(get_arg(args, OPTION, NULL), str);
		else if (str[0] == '-' && (simple || str[1] == '-'))
			ret = parse_args_param(args, ac, av, &i);
		else
			parse_add2lst(&lst, str);
		if (ret)
			return (-1);
	}
	return (make_default_args(args, &lst) || validate_args(args) ? -1 : 0);
}
