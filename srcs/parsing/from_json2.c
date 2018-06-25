/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from_json2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/25 16:57:48 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/25 17:06:49 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int					int_from_json(const t_json_value *val, int *i)
{
	if (val && val->n_i.type == JSON_INT)
	{
		*i = val->n_i.value;
		return (1);
	}
	return (0);
}
