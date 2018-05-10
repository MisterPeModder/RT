/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/06 19:11:40 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/10 17:22:41 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/stringft.h>
#include <libft_base/io.h>
#include <stdlib.h>
#include "rtv1.h"

t_img				*img_make(unsigned int w, unsigned int h)
{
	t_img			*img;
	unsigned int	x;

	if (!(img = (t_img *)malloc(sizeof(t_img))))
		return (NULL);
	img->w = w;
	img->h = h;
	if (!(img->data = (t_color **)malloc(sizeof(t_color *) * w)))
	{
		free(img);
		return (NULL);
	}
	x = 0;
	while (x < w)
		if (!(img->data[x++] = (t_color *)malloc(sizeof(t_color) * h)))
		{
			w = x - 1;
			x = 0;
			while (x < w)
				free(img->data[x++]);
			free(img->data);
			free(img);
			return (NULL);
		}
	return (img);
}

void				img_release(t_img **img)
{
	unsigned int	x;

	if (!img || !*img)
		return ;
	if ((*img)->data)
	{
		x = 0;
		while (x < (*img)->w)
			free((*img)->data[x++]);
		free((*img)->data);
	}
	free(*img);
	*img = NULL;
}

void				img_ppm_output(t_img *img)
{
	char			*tmp;
	unsigned int	x;
	unsigned int	y;

	ft_putendl("P6");
	ft_putstr((tmp = ft_itoa((int)img->w)));
	free(tmp);
	ft_putchar(' ');
	ft_putendl((tmp = ft_itoa((int)img->h)));
	free(tmp);
	ft_putendl("255");
	y = 0;
	while (y < img->h)
	{
		x = 0;
		while (x < img->w)
		{
			ft_putchar((char)img->data[x][y][0]);
			ft_putchar((char)img->data[x][y][1]);
			ft_putchar((char)img->data[x++][y][2]);
		}
		++y;
	}
}
