/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:39:41 by yguaye            #+#    #+#             */
/*   Updated: 2017/12/21 14:50:36 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include <string.h>

void				ft_bzero(void *s, size_t n);

void				*ft_memalloc(size_t size);

void				*ft_memchr(const void *s, int ch, size_t n);

int					ft_memcmp(const void *s1, const void *s2, size_t n);

void				*ft_memcpy(void *dst, const void *src, size_t n);

void				*ft_memccpy(void *d, const void *s, int c, size_t n);

void				ft_memdel(void **ap);

void				*ft_memdup(const void *src, size_t size);

void				*ft_memmove(void *d, const void *s, size_t n);

void				*ft_memset(void *b, int c, size_t len);

#endif
