/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_pushback.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:42:47 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/15 16:40:42 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

void		ft_lst_pushback(t_list *begin_list, t_list *nl)
{
	if (!begin_list)
		return ;
	while (begin_list->next)
		begin_list = begin_list->next;
	begin_list->next = nl;
}
