/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:43:27 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/28 17:57:22 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_H
# define LIST_H

# include <string.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

void				ft_lstadd(t_list **alst, t_list *nlst);

void				ft_lstdel(t_list **alst, void (*del)(void *, size_t));

void				ft_lstdelone(t_list **alst, void (*del)(void *, size_t));

t_list				*ft_lstextract(t_list **lst, void *target,
		int (*cmp)(void *, void *));

void				ft_lstiter(t_list *lst, void (*f)(t_list *elem));

size_t				ft_lstlen(t_list *lst);

t_list				*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_list				*ft_lstnew(void const *content, size_t content_size);

void				ft_lstrem(t_list **beg, t_list *lst);

void				ft_lst_pushback(t_list *begin_list, t_list *nl);

#endif
