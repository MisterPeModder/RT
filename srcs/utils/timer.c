/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:16:26 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/16 11:32:13 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <sys/time.h>
#include <libft_base/io.h>
#include "timer.h"

void				timer_start(t_timer *timer)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	timer->val = start.tv_sec * 1000000 + start.tv_usec;
	timer->secs = 0;
	timer->msecs = 0;
}

void				timer_end(t_timer *timer)
{
	struct timeval	end;
	long long		tmp;

	gettimeofday(&end, NULL);
	tmp = end.tv_sec * 1000000 + end.tv_usec - timer->val;
	timer->msecs = tmp % 1000000;
	timer->secs = tmp / 1000000;
}

float				timer_span(t_timer *timer)
{
	return ((float)timer->secs + (float)timer->msecs / 1000000.f);
}

static void			put_microseconds(int nbr)
{
	int				buff[6];
	int				i;

	i = 6;
	while (--i >= 0)
	{
		buff[i] = nbr % 10;
		nbr /= 10;
	}
	i = 0;
	while (i < 6)
		ft_putchar(buff[i++] + '0');
}

void				timer_display(t_timer *timer, const char *msg)
{
	if (msg)
		ft_putstr(msg);
	ft_putnbr(timer->secs);
	ft_putchar('.');
	put_microseconds(timer->msecs);
	ft_putstr("s\n");
}
