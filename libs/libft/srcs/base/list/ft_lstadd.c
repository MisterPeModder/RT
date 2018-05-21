/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:14:47 by yguaye            #+#    #+#             */
/*   Updated: 2017/12/16 16:02:01 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

void		ft_lstadd(t_list **alst, t_list *nlst)
{
	t_list	*tmp;

	if (!alst || !*alst)
		*alst = nlst;
	else
	{
		tmp = *alst;
		*alst = nlst;
		nlst->next = tmp;
	}
}
