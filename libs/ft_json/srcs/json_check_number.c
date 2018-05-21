/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   json_check_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 05:46:30 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 06:04:46 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/character.h>
#include "json_internal.h"

static int				json_nb_check_start(const char *s,
		t_json_parse_res *r, int *i)
{
	*i = *s == '-' ? 1 : 0;
	if (s[*i] == '-')
		return (json_ret_errorv(r, "too many minus signs"));
	if (!s[*i])
		return (json_ret_errorv(r, "unexpected token"));
	if (s[*i] == '0' && s[*i + 1] && ft_isdigit(s[*i + 1]))
		return (json_ret_errorv(r, "trailing zero(s)"));
	if (s[*i] != '0')
		while (s[++*i] && ft_isdigit(s[*i]))
			;
	else
		++*i;
	return (1);
}

int						json_number_check(const char *s, t_json_parse_res *r)
{
	int					i;

	if (!json_nb_check_start(s, r, &i))
		return (0);
	if (!s[i])
		return (1);
	if (s[i] == '.')
	{
		if (!ft_isdigit(s[i + 1]))
			return (json_ret_errorv(r, "missing decimals"));
		while (s[++i] && ft_isdigit(s[i]))
			;
	}
	if (!s[i])
		return (1);
	if (s[i] == 'e' || s[i] == 'E')
	{
		if (!s[++i] || ((s[i] == '+' || s[i] == '-') && !s[i + 1]))
			return (json_ret_errorv(r, "missing number after exponent"));
		if (s[i] == '+' || s[i] == '-')
			++i;
		while (s[i] && ft_isdigit(s[i++]))
			;
	}
	return (s[i] ? json_ret_errorv(r, "trailing character(s)") : 1);
}
