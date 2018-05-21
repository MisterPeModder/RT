/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 14:54:33 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/03 15:00:56 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_containers/dyn_str.h"

void				dynstr_del(t_dynstr **str)
{
	if (!str || !*str)
		return ;
	if ((*str)->str)
		free((*str)->str);
	free(*str);
	*str = NULL;
}

void				dynstr_deinit(t_dynstr *str)
{
	if (str && str->str)
	{
		free(str->str);
		str->str = NULL;
	}
}
