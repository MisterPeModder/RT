/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse_default.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/18 14:40:34 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/19 11:28:06 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/list.h"
#include "libft_base/memory.h"
#include "libft_base/stringft.h"
#include "libft_args/args.h"

static char		**dargs_lst2array(t_list *lst)
{
	char		**tab;
	int			i;

	if (!(tab = (char **)ft_memalloc(sizeof(char *) * (ft_lstlen(lst) + 1))))
		return (NULL);
	i = 0;
	while (lst)
	{
		tab[i++] = ft_strdup(lst->content);
		lst = lst->next;
	}
	return (tab);
}

int				make_default_args(t_args *args, t_list **lst)
{
	t_arglst		*curr;

	if (!lst || !*lst)
		return (0);
	if (!(curr = new_arg(DEFAULT, args, NULL)))
		return (set_arg_error(args, ARG_MEM_ERROR, NULL));
	if (!(curr->argv.d.argv = dargs_lst2array(*lst)))
		return (set_arg_error(args, ARG_MEM_ERROR, NULL));
	curr->argv.d.argc = ft_strtablen((const char **)curr->argv.d.argv);
	ft_lstdel(lst, (void (*)(void *, size_t))&free);
	return (0);
}
