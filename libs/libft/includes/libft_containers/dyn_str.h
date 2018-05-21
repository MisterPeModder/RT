/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dyn_str.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/03 14:16:29 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/03 15:00:18 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DYN_STR_H
# define DYN_STR_H

# include <stdlib.h>

typedef struct		s_dynstr
{
	char			*str;
	size_t			length;
	size_t			capacity;
	size_t			increment;
}					t_dynstr;

t_dynstr			*dynstr_make(size_t capacity);
void				dynstr_init(t_dynstr *str, size_t capacity);
void				dynstr_push(t_dynstr *str, const char *c);
void				dynstr_pushc(t_dynstr *str, char c);
void				dynstr_del(t_dynstr **str);
void				dynstr_deinit(t_dynstr *str);

#endif
