/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 18:06:32 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/25 19:40:22 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <unistd.h>
#include "rt.h"

static int			show_usage(int out)
{
	ft_putendl_fd("usage: rt [-h | -o=<options_path>] <scene_path>", out);
	return (out == STDERR_FILENO ? 1 : 2);
}

static int			parse_options_path(char *arg, char **options_path)
{
	if (arg[0] != '=' || !arg[1])
	{
		ft_putendl_fd("missing options path", STDERR_FILENO);
		return (1);
	}
	*options_path = arg + 1;
	return (0);
}

static int			handle_scene_arg(int *sc, int i, int ac)
{
	if (*sc || i != ac - 1)
	{
		ft_putendl_fd(*sc ? "cannot have more than one scene" :
				"scene must be the last argument", STDERR_FILENO);
		return (1);
	}
	*sc = 1;
	return (0);
}

static int			parse_options(int ac, char **av, char **options_path)
{
	int				i;
	int				sc;

	sc = 0;
	i = 0;
	while (++i < ac)
	{
		if (*av[i] == '-')
		{
			if (av[i][1] == 'h' && !av[i][2])
				return (show_usage(STDOUT_FILENO));
			else if (av[i][1] == 'o' && parse_options_path(av[i] + 2,
						options_path))
				return (3);
			else if (av[i][1] != 'o')
			{
				ft_putstr_fd("illegal option: ", STDERR_FILENO);
				ft_putendl_fd(av[i], STDERR_FILENO);
				return (3);
			}
		}
		else if (handle_scene_arg(&sc, i, ac))
			return (3);
	}
	return (0);
}

int					parse_args(int ac, char **av, char **options_path)
{
	int				ret;

	if (ac <= 1)
		return (show_usage(STDERR_FILENO));
	*options_path = NULL;
	if ((ret = parse_options(ac, av, options_path)))
	{
		if (ret == 1)
		{
			ft_putendl_fd("missing scene file", STDERR_FILENO);
			return (1);
		}
		return (ret == 2 ? 2 : 1);
	}
	if (!*options_path)
		*options_path = DEFAULT_OPTIONS;
	return (0);
}
