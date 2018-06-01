/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:16:26 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/31 19:30:20 by yguaye           ###   ########.fr       */
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
}

void				timer_end(t_timer *timer)
{
	struct timeval	end;
	long long		tmp;

	gettimeofday(&end, NULL);
	tmp = end.tv_sec * 1000000 + end.tv_usec - timer->val;
	timer->msecs = tmp % 100000;
	timer->secs = tmp / 100000;
}

float				timer_span(t_timer *timer)
{
	return ((float)timer->secs + (float)timer->msecs / 100000.f);
}

void				timer_display(t_timer *timer, const char *msg)
{
	if (msg)
		ft_putstr(msg);
	ft_putnbr(timer->secs);
	ft_putchar('.');
	ft_putnbr(timer->msecs);
	ft_putchar('\n');
}
