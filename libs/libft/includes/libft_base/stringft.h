/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stringft.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/21 14:35:39 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/05 04:23:20 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRINGFT_H
# define STRINGFT_H

# include <string.h>

int					ft_atoi(const char *str);

long				ft_atol(const char *str);

char				*ft_itoa(int n);

char				*ft_dtoa(double n, unsigned int prec);

char				*ft_ltoa(long n);

char				*ft_strcat(char *dest, const char *src);

char				*ft_strchr(const char *s, int ch);

void				ft_strclr(char *s);

int					ft_strcmp(const char *s1, const char *s2);

char				*ft_strcpy(char *dst, const char *src);

char				*ft_strconcat(char *s1, char *s2, int free_args);

void				ft_strdel(char **as);

char				*ft_strdup(const char *str);

int					ft_strequ(char const *s1, char const *s2);

size_t				ft_strlcat(char *dst, const char *src, size_t size);

size_t				ft_strlen(const char *s);

char				*ft_strlowcase(char *str);

void				ft_striter(char *s, void (*f)(char *));

void				ft_striteri(char *s, void (*f)(unsigned int, char *));

int					ft_strisnumber(char *str);

char				*ft_strjoin(char const *s1, char const *s2);

char				*ft_strjoinf(char **s1, char **s2);

char				*ft_strjoinf1(char **s1, const char *s2);

char				*ft_strjoinf2(const char *s1, char **s2);

char				*ft_strmap(char const *s, char (*f)(char));

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));

char				*ft_strncat(char *dest, const char *src, size_t n);

int					ft_strncmp(const char *s1, const char *s2, size_t n);

int					ft_strnequ(char const *s1, char const *s2, size_t n);

char				*ft_strnew(size_t size);

char				*ft_strnstr(const char *haystack,
		const char *needle, size_t len);

char				*ft_strncpy(char *dst, const char *src, size_t len);

char				*ft_strrchr(const char *s, int ch);

char				**ft_strsplit(char const *s, char c);

char				*ft_strstr(const char *haystack, const char *needle);

char				*ft_strsub(char const *s, unsigned int start, size_t len);

void				ft_strtabdel(char ***tab);

size_t				ft_strtablen(const char **tab);

char				*ft_strtrim(char const *s);

char				*ft_strupcase(char *str);

#endif
