/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 14:40:35 by jhache            #+#    #+#             */
/*   Updated: 2018/05/29 03:01:53 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_data.h"
#include <libft_base/io.h>
#include <libft_base/stringft.h>
#include <libft_base/memory.h>

void				*free_strtab(char **tab, size_t size)
{
	size_t			i;

	i = 0;
	if (tab == NULL)
		return (NULL);
	while (i < size)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

static void			*alloc_strtab(char **tab, size_t size)
{
	char			**res;
	size_t			i;

	if (!(res = (char **)malloc(sizeof(char *) * (size + TAB_STEP_SIZE))))
		return (NULL);
	i = 0;
	while (i < size)
		res[i++] = NULL;
	if (tab)
	{
		ft_memcpy(res, tab, sizeof(char *) * size);
		free(tab);
	}
	return (res);
}

char				**read_src_file(const char *file_name, size_t *size)
{
	int		fd;
	int		ret;
	char	**result;
	char	buff[BUFF_SIZE + 1];

	fd = open(file_name, O_RDONLY);
	if ((*size = 0) || fd <= 0 || size == NULL)
		return (NULL);
	result = NULL;
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (*size % TAB_STEP_SIZE == 0)
		{
			if (!(result = alloc_strtab(result, *size)))
				return (free_strtab(result, *size));
		}
		buff[ret] = '\0';
		result[*size] = ft_strdup(buff);
		*size += 1;
	}
	close(fd);
	if (ret < 0)
		return (free_strtab(result, *size));
	return (result);
}
