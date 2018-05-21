/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:29:09 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/14 16:35:46 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"
#include <stdlib.h>

static t_list	*add_map(t_list **nl, t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*elem;
	t_list	*tmp;

	if (lst->next && !add_map(nl, lst->next, f))
		return (NULL);
	if (!(elem = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	tmp = (*f)(lst);
	elem->content = tmp->content;
	elem->content_size = tmp->content_size;
	elem->next = *nl;
	*nl = elem;
	return (*nl);
}

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*nl;

	if (!lst)
		return (NULL);
	nl = (t_list *)NULL;
	return (add_map(&nl, lst, f));
}
