/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 11:28:30 by yguaye            #+#    #+#             */
/*   Updated: 2017/12/21 11:33:05 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_base/base.h"

void		*ft_memdup(const void *src, size_t size)
{
	void	*dst;

	if (!(dst = malloc(size)))
		return (NULL);
	return (ft_memcpy(dst, src, size));
}
