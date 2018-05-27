/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_kernel.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 14:40:35 by jhache            #+#    #+#             */
/*   Updated: 2018/05/27 15:10:31 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_data.h"
#include <libft_base/io.h>
#include <libft_base/stringft.h>
#include <libft_base/memory.h>

void				*free_strtab(char **tab, unsigned int str_nb)
{
	unsigned int	i;

	i = 0;
	if (tab == NULL)
		return (NULL);
	while (i < str_nb)
		free(tab[i++]);
	free(tab);
	return (NULL);
}

void				*ft_realloc(void *src, size_t len, size_t added)
{
	void			*result;

	result = ft_memalloc(sizeof(len));
	if (src != NULL)
		ft_memmove(result, src, len - added);
	return (result);
}

char				**read_src_file(const char *file_name, cl_uint *size)
{
	int		fd;
	int		ret;
	char	**result;
	char	buff[BUFF_SIZE + 1];

	fd = open(file_name, O_RDONLY);
	if ((*size = 0) || fd <= 0 || size == NULL)
		return (NULL);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		if (*size % TAB_STEP_SIZE == 0)
		{
			if (!(result = ft_realloc(result, sizeof(char *)
							* (*size + TAB_STEP_SIZE),
							TAB_STEP_SIZE)))
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
