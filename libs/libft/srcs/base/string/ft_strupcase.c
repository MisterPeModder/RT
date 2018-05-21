/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 23:14:10 by yguaye            #+#    #+#             */
/*   Updated: 2017/11/14 16:52:25 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_base/base.h"

static void	ft_char_toupper(char *c)
{
	*c = ft_toupper(*c);
}

char		*ft_strupcase(char *str)
{
	ft_striter(str, &ft_char_toupper);
	return (str);
}
