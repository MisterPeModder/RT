/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 16:51:34 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/15 16:41:51 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

static void	ft_char_tolower(char *c)
{
	*c = ft_tolower(*c);
}

char		*ft_strlowcase(char *str)
{
	ft_striter(str, &ft_char_tolower);
	return (str);
}
