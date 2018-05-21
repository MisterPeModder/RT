/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 21:26:50 by yguaye            #+#    #+#             */
/*   Updated: 2018/01/07 16:57:16 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

static char	*create_str(int n)
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

static void	putnum(char *buf, int n)
{
	if (n == -2147483648)
	{
		ft_strcpy(buf, "-2147483648");
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

char		*ft_itoa(int n)
{
	char	*buf;

	if (!(buf = create_str(n)))
		return (NULL);
	putnum(buf, n);
	return (buf);
}
