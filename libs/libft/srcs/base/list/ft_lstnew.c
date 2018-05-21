/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 21:40:18 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/13 22:27:33 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"
#include <stdlib.h>

t_list		*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*lst;
	void	*new_content;

	if (!(lst = (t_list *)malloc(sizeof(t_list))))
		return ((t_list *)NULL);
	lst->next = (t_list *)NULL;
	if (content && (new_content = malloc(content_size)))
	{
		lst->content = ft_memcpy(new_content, content, content_size);
		lst->content_size = content_size;
		return (lst);
	}
	lst->content = NULL;
	lst->content_size = (size_t)0;
	return (lst);
}
