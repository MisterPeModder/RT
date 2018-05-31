/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:07:58 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/31 15:47:15 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
# define TIMER_H

/*
** t_timer: A easy-to-use timer.
**
** -secs the elapsed seconds between start and end
** -msecs the elapsed nanoseconds between start and end
*/
typedef struct		s_timer
{
	long long		val;
	int				secs;
	int				msecs;
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

/*
** timer_display: Print the elapsed time into standard output.
**
** -msg: a message string that will be printed before time. can be NULL
*/
void				timer_display(t_timer *timer, const char *msg);

#endif
