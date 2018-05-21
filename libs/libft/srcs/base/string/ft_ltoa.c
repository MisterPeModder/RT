/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/05 00:20:51 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 02:24:54 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

static char	*create_str(long n)
{
	size_t	len;

	len = n < 0 ? 2 : 1;
	while (n > 10 || n < -10)
	{
		n /= 10;
		++len;
	}
	++len;
	return (ft_strnew(len));
}

static void	append(char *buf, char c)
{
	while (*buf)
		++buf;
	*buf = c;
}

static void	putnum(char *buf, long n)
{
	if (n == -9223372036854775807)
	{
		ft_strcpy(buf, "-9223372036854775807");
		return ;
	}
	else if (n < 0)
	{
		append(buf, '-');
		n = -n;
	}
	if (n < 10)
		append(buf, '0' + n % 10);
	else
	{
		putnum(buf, n / 10);
		append(buf, '0' + n % 10);
	}
}

char		*ft_ltoa(long n)
{
	char	*buf;

	if (!(buf = create_str(n)))
		return (NULL);
	putnum(buf, n);
	return (buf);
}
