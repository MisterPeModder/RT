/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 03:44:52 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 06:19:55 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdlib.h>
#include "libft_base/stringft.h"
#include "libft_math/calc.h"

static int				handle_no_number_after_decimal(unsigned int prec,
		char **s)
{
	char		*s_tmp;
	int			i;

	i = 0;
	if (!(s_tmp = (char *)malloc(sizeof(char) * (prec + 1))))
		return (1);
	while (prec--)
		s_tmp[i++] = '0';
	s_tmp[i] = '\0';
	ft_strcat(*s, s_tmp);
	ft_strdel(&s_tmp);
	return (0);
}

static unsigned int		ft_longlen(long n)
{
	unsigned int		len;

	if (n == LONG_MIN)
		return (20);
	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static int				precision_smaller_than_10(double n, unsigned int prec,
		char **s)
{
	char				*s_tmp;
	unsigned int		prec_tmp;
	int					i;

	i = 0;
	n *= ft_pow(10, (int)prec);
	prec_tmp = prec - ft_longlen(n);
	if (!(s_tmp = (char *)malloc(sizeof(char) * (prec_tmp + 1))))
		return (1);
	while (prec_tmp--)
		s_tmp[i++] = '0';
	s_tmp[i] = '\0';
	if ((long)((n - (long)n) * 10) > 4)
		n += 1;
	ft_strcat(*s, s_tmp);
	ft_strdel(&s_tmp);
	ft_strcat(*s, s_tmp = ft_ltoa(n));
	ft_strdel(&s_tmp);
	return (0);
}

static int				handle_precision(double n, unsigned int prec, char **s)
{
	char		*s_tmp;

	if ((n = n - (long)n))
	{
		if (prec < 10)
			precision_smaller_than_10(n, prec, s);
		else
		{
			while (prec--)
			{
				n *= 10;
				if (!prec && (long)((n - (long)n) * 10) > 4
						&& (long)((n - (long)n) * 10) != 9)
					n += 1;
				ft_strcat(*s, s_tmp = ft_ltoa(n));
				ft_strdel(&s_tmp);
				n -= (long)n;
			}
		}
	}
	else
		handle_no_number_after_decimal((size_t)prec, s);
	return (0);
}

char					*ft_dtoa(double n, unsigned int prec)
{
	char		*s;
	char		*s_tmp;
	size_t		len;

	len = ft_longlen(n) + prec + 1;
	if (!(s = ft_strnew(len)))
		return (NULL);
	s[0] = '\0';
	if (n < 0 ? 1 : 0)
	{
		n = -n;
		s[0] = '-';
		s[1] = '\0';
	}
	ft_strcat(s, s_tmp = ft_ltoa(n));
	ft_strdel(&s_tmp);
	if (prec)
	{
		ft_strcat(s, ".");
		if (handle_precision(n, prec, &s))
			return (NULL);
	}
	return (s);
}
