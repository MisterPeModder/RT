/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_to_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 16:43:55 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 16:57:55 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include "json.h"

int						json_to_file(const t_json_value *obj, int fd)
{
	char				**tab;
	size_t				i;

	if (!(tab = json_to_tab(obj)))
		return (0);
	i = 0;
	while (tab[i])
	{
		ft_putendl_fd(tab[i], fd);
		free(tab[i]);
		++i;
	}
	free(tab);
	return (1);
}
