/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrem.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 14:37:16 by yguaye            #+#    #+#             */
/*   Updated: 2017/12/17 14:49:30 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

void		ft_lstrem(t_list **beg, t_list *target)
{
	t_list	*lst;
	t_list	*prev;

	if (!beg || !*beg)
		return ;
	lst = *beg;
	prev = NULL;
	while (lst)
	{
		if (lst == target)
		{
			if (prev)
				prev->next = lst->next;
			else if (lst == *beg)
				*beg = (*beg)->next;
			lst->next = NULL;
			return ;
		}
		else
			prev = lst;
		lst = lst->next;
	}
}
