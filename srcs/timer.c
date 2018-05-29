/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:16:26 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 13:31:12 by yguaye           ###   ########.fr       */
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
	int				i;

	gettimeofday(&end, NULL);
	timer->val = end.tv_sec * 1000000 + end.tv_usec - timer->val;
	timer->nsecs = timer->val % 1000000;
	i = -1;
	while (++i < 6)
		timer->val /= 10;
	timer->secs = timer->val;
}

void				timer_display(t_timer *timer, const char *msg)
{
	if (msg)
		ft_putstr(msg);
	ft_putnbr(timer->secs);
	ft_putchar('.');
	ft_putnbr(timer->nsecs);
	ft_putchar('\n');
}
