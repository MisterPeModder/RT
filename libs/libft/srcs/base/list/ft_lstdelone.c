/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 22:01:39 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/15 17:05:39 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

void		ft_lstdelone(t_list **alst, void (*del)(void *, size_t))
{
	if (del)
		(*del)((*alst)->content, (*alst)->content_size);
	ft_memdel((void **)alst);
}
