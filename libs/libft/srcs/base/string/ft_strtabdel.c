/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtabdel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 13:59:54 by yguaye            #+#    #+#             */
/*   Updated: 2017/12/16 16:32:51 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"
#include <stdlib.h>

void		ft_strtabdel(char ***tab)
{
	char	**tmp;

	tmp = *tab;
	while (*tmp)
	{
		ft_strclr(*tmp);
		free(*tmp);
		++tmp;
	}
	ft_memdel((void **)tab);
}
