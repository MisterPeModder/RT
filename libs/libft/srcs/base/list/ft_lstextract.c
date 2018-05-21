/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstextract.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/17 13:45:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/06 18:14:01 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

t_list				*ft_lstextract(t_list **lst, void *target,
		int (*cmp)(void *, void *))
{
	t_list		*tmp;

	if (!lst || !*lst)
		return (NULL);
	tmp = *lst;
	while (tmp)
	{
		if (!(*cmp)(target, tmp->content))
		{
			ft_lstrem(lst, tmp);
			tmp->next = NULL;
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}
