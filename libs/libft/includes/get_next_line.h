/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/09 11:53:20 by yguaye            #+#    #+#             */
/*   Updated: 2017/12/09 14:32:17 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 9999

typedef struct	s_buff
{
	char		*buf;
	int			count;
	int			i;
	int			nl;
	int			fd;
}				t_buff;
int				get_next_line(int const fd, char **line);
#endif
