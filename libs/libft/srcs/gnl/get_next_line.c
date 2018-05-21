/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/30 14:46:00 by yguaye            #+#    #+#             */
/*   Updated: 2018/04/19 11:22:04 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>

static t_buff	*gnl_buff(t_list **lst, int fd)
{
	t_buff	*gnl;
	t_list	*temp;

	temp = *lst;
	while (temp)
	{
		gnl = (t_buff *)(temp->content);
		if (gnl->fd == fd)
			return (gnl);
		temp = temp->next;
	}
	gnl = (t_buff *)ft_memalloc(sizeof(t_buff));
	gnl->buf = ft_strnew(BUFF_SIZE);
	gnl->count = BUFF_SIZE;
	gnl->i = BUFF_SIZE;
	gnl->fd = fd;
	gnl->nl = 1;
	temp = ft_lstnew(gnl, sizeof(t_buff));
	ft_memdel((void **)&gnl);
	ft_lstadd(lst, temp);
	return ((t_buff *)(temp->content));
}

static char		*get_reminder(char **a, t_buff *gnl)
{
	int		i;
	char	*rem;
	char	*tmp;

	i = 0;
	gnl->nl = 0;
	while (gnl->i + i < gnl->count)
	{
		if (gnl->buf[gnl->i + i] == '\n')
		{
			gnl->nl = 1;
			i++;
			break ;
		}
		i++;
	}
	gnl->i += i;
	rem = ft_strsub(gnl->buf, (unsigned int)(gnl->i - i),
			(size_t)(i - gnl->nl));
	tmp = ft_strjoin(*a, rem);
	ft_strdel(a);
	ft_strdel(&rem);
	return (tmp);
}

static int		gnl_free(t_list **lst, int fd, char **str)
{
	t_buff	*gnl;
	t_list	**temp;
	t_list	*ptr;

	temp = lst;
	while (*temp)
	{
		gnl = (t_buff *)((*temp)->content);
		if (gnl->fd == fd)
			break ;
		*temp = ((*temp)->next);
	}
	if (*temp)
	{
		ptr = (*temp)->next;
		ft_strdel(&(gnl->buf));
		ft_memdel((void **)&gnl);
		ft_memdel((void **)temp);
		*temp = ptr;
	}
	ft_strdel(str);
	return (0);
}

static int		gnl_check(t_buff *gnl, t_list **lst, char **temp, char **line)
{
	if (gnl->i == gnl->count)
	{
		gnl->count = read(gnl->fd, gnl->buf, BUFF_SIZE);
		if (gnl->count == -1)
		{
			gnl_free(lst, gnl->fd, temp);
			return (-1);
		}
		gnl->i = 0;
		if (gnl->count == 0)
		{
			if (gnl->nl == 0)
			{
				*line = *temp;
				return (1);
			}
		}
	}
	return (0);
}

int				get_next_line(int const fd, char **line)
{
	static t_list	*lst;
	t_buff			*gnl;
	char			*tmp;
	int				ret;

	if (fd < 0 || line == NULL)
		return (-1);
	gnl = gnl_buff(&lst, fd);
	tmp = ft_strnew(0);
	while (gnl->count > 0)
	{
		if ((ret = gnl_check(gnl, &lst, &tmp, line)) != 0)
			return (ret);
		while (gnl->i < gnl->count)
		{
			tmp = get_reminder(&tmp, gnl);
			if (gnl->nl)
			{
				*line = tmp;
				return (1);
			}
		}
	}
	return (gnl_free(&lst, fd, &tmp));
}
