/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtablen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 01:41:58 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/23 12:31:48 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

size_t		ft_strtablen(const char **tab)
{
	size_t	size;

	size = 0;
	while (tab && tab[size])
		++size;
	return (size);
}
