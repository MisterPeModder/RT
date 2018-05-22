/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:31:53 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/22 19:06:01 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include <libft_base/io.h>
#include <unistd.h>
#include "rt.h"

int					read_args(int ac, char **av)
{
	if (ac == 4)
	{
		if (!(ft_strequ(av[2], "--output") || ft_strequ(av[2], "-o")))
		{
			ft_putendl_fd("Second paremeter must be either '-o' or '--output'",
					STDERR_FILENO);
			return (-1);
		}
		if (ft_strequ(av[3], "mlx"))
			return (1);
		else if (ft_strequ(av[3], "ppm"))
			return (0);
		else
			ft_putendl_fd("Unknown output format, use 'mlx' or 'ppm' instead",
					STDERR_FILENO);
	}
	else if (ac == 2)
		return (1);
	else
		ft_putendl_fd("Wrong number of arguments", STDERR_FILENO);
	return (-1);
}
