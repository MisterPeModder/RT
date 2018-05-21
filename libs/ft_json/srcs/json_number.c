/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_number.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/24 14:53:29 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 06:13:08 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include <libft_math/calc.h>
#include "json_internal.h"

static double			json_parse_dpart(const char *src)
{
	double				r;

	r = ft_atol(src);
	r = r < 0 ? -r : r;
	while (r >= 1)
		r /= 10.;
	while (*src && *src == '0')
	{
		r /= 10.;
		++src;
	}
	return (r);
}

static double			json_num_get_exp(const char *src)
{
	while (*src && *src != 'E' && *src != 'e')
		++src;
	if (!*src || !*(src + 1))
		return (1);
	return (ft_pow(10., atoi(src + 1)));
}

int						json_make_number(t_json_value *num, const char *src,
		t_json_parse_res *r)
{
	int					e_part;
	double				a_part;

	if (!json_number_check(src, r))
		return (0);
	e_part = ft_atoi(src);
	while (*src && *src != '.' && *src != 'E' && *src != 'e')
		++src;
	if (*src == '.')
	{
		num->n_d.type = JSON_DOUBLE;
		a_part = e_part < 0 ? -e_part : e_part;
		num->n_d.value = a_part + json_parse_dpart(++src);
		num->n_d.value *= e_part < 0 ? -1 : 1;
		num->n_d.value *= json_num_get_exp(src);
	}
	else
	{
		num->n_i.type = JSON_INT;
		num->n_i.value = e_part;
		num->n_i.value *= json_num_get_exp(src);
	}
	return (1);
}

char					*json_suppress_zeros(char *str)
{
	int					i;

	if (!str)
		return (NULL);
	i = -1;
	while (str[++i])
		;
	--i;
	while (i > 0 && str[i] == '0' && str[i - 1] != '.')
		str[i--] = 0;
	return (str);
}
