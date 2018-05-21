/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr_make.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 14:24:24 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/03 14:38:24 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_containers/dyn_str.h"

t_dynstr			*dynstr_make(size_t capacity)
{
	t_dynstr		*str;

	if (!(str = (t_dynstr *)malloc(sizeof(t_dynstr))))
		return (NULL);
	str->str = NULL;
	str->increment = capacity;
	str->capacity = capacity;
	str->length = 0;
	return (str);
}

void				dynstr_init(t_dynstr *str, size_t capacity)
{
	str->str = NULL;
	str->increment = capacity;
	str->capacity = capacity;
	str->length = 0;
}
