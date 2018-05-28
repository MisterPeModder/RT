/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:07:58 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/28 16:32:18 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

/*
** t_timer: A easy-to-use timer.
**
** -secs the elapsed seconds between start and end
** -nsecs the elapsed nanoseconds between start and end
*/
typedef struct		s_timer
{
	long long		val;
	int				secs;
	int				nsecs;
}					t_timer;

/*
** timer_start: starts/restarts the timer.
**
** -timer: a valid pointer to a timer structure, MUST BE A VALID POINTER.
*/
void				timer_start(t_timer *timer);

/*
** timer_end: end the timer.
**
** -timer: a valid pointer to a timer structure, MUST BE A VALID POINTER.
**
** NOTE: this function must only be called ONCE AFTER the timer has started or
** its behavior is undefined.
*/
void				timer_end(t_timer *timer);

void				timer_display(t_timer *timer);

#endif
