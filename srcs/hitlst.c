/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hitlst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/07 23:34:01 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/08 11:15:09 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "rtv1.h"

t_hitlst			*hitlstnew(t_object *obj, float dist, t_vec3f *pos,
		t_vec3f *normal)
{
	t_hitlst		*lst;

	if (!(lst = (t_hitlst *)malloc(sizeof(t_hitlst))))
		return (NULL);
	lst->r.obj = obj;
	lst->r.pos = *pos;
	lst->r.normal = *normal;
	vec3f_normalize(&lst->r.normal, &lst->r.normal);
	lst->r.dist = dist;
	lst->next = NULL;
	return (lst);
}

void				hitlstdel(t_hitlst *lst)
{
	t_hitlst		*tmp;

	while (lst)
	{
		tmp = lst->next;
		free(lst);
		lst = tmp;
	}
}

t_hitlst			*hitlstjoin(t_hitlst *big, t_hitlst *small)
{
	t_hitlst		*end;

	if (!big)
		return (small);
	if (!small)
		return (big);
	end = small;
	while (end->next)
		end = end->next;
	end->next = big;
	return (small);
}
