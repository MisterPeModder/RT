/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/23 10:17:40 by yguaye            #+#    #+#             */
/*   Updated: 2018/08/23 11:11:52 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <libft_base/io.h>
#include "rt.h"

static void			put_pixel_img(int x, int y, int fd, t_rt *core)
{
	Uint8			r;
	Uint8			g;
	Uint8			b;

	SDL_GetRGB(((Uint32 *)core->sdl.screen->pixels)[x
			+ (y * core->sdl.screen->w)],
			core->sdl.screen->format, &r, &g, &b);
	ft_putchar_fd((char)r, fd);
	ft_putchar_fd((char)g, fd);
	ft_putchar_fd((char)b, fd);
}

static void			give_status(int current, int max, int *stage)
{
	if (*stage < 100 && current >= (float)max * ((float)*stage / 100.f))
	{
		if (*stage == 0)
			ft_putchar(' ');
		ft_putchar(' ');
		ft_putnbr(*stage);
		ft_putendl("%");
	}
	else
		return ;
	*stage += 10;
}

static void			give_final_status(int fd, t_rt *core)
{
	close(fd);
	ft_putstr("100%\nTook a ");
	ft_putnbr(core->sdl.screen->w);
	ft_putchar('x');
	ft_putnbr(core->sdl.screen->h);
	ft_putendl(" screenshot, saved to 'screenshot.ppm'");
}

void				take_screeshot(t_rt *core)
{
	int				fd;
	int				y;
	int				x;
	int				stage;

	ft_putendl("Taking screenshot...");
	if ((fd = open("./screenshot.ppm", O_WRONLY | O_CREAT, 0644)) == -1)
		return ;
	ft_putendl_fd("P6", fd);
	ft_putnbr_fd(core->sdl.screen->w, fd);
	ft_putchar_fd(' ', fd);
	ft_putnbr_fd(core->sdl.screen->h, fd);
	ft_putendl_fd(" 255", fd);
	y = -1;
	stage = 0;
	while (++y < core->sdl.screen->h && (x = -1))
	{
		while (++x < core->sdl.screen->w)
		{
			put_pixel_img(x, y, fd, core);
			give_status(x + (y * core->sdl.screen->w),
					core->sdl.screen->w * core->sdl.screen->h, &stage);
		}
	}
	give_final_status(fd, core);
}
