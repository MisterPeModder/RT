/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/07 10:55:32 by yguaye            #+#    #+#             */
/*   Updated: 2018/02/07 16:23:24 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H
# if defined DEBUG && DEBUG != 0

#  include <stdio.h>

#  define DB_IF __FILE__ , __func__ , __LINE__
#  define DB_VA __VA_ARGS__

#  define PTRACE printf("## %s:%s@%d\n", DB_IF)
#  define TRACE(N) (printf("## %s (%s:%s@%d)\n", N, DB_IF) * 0)
#  define TRACEN(N) (printf("## %s (%s:%s@%d)", N, DB_IF) * 0)

#  define TRACE_CLL(N, ...) (TRACE(#N"("#__VA_ARGS__")") + N(__VA_ARGS__))
#  define TRACE_VAL(N, F, X) (X + TRACEN(N) + printf(" ## value="F"\n", X) * 0)

#  define TRACE_INT(NAME, X) TRACE_VAL(NAME, "%d", X)
#  define TRACE_UIN(NAME, X) TRACE_VAL(NAME, "%u", (unsigned int)X)
#  define TRACE_LNG(NAME, X) TRACE_VAL(NAME, "%ld", (long)X)
#  define TRACE_ULN(NAME, X) TRACE_VAL(NAME, "%lu", (unsigned long)X)
#  define TRACE_DBL(NAME, X) TRACE_VAL(NAME, "%f", X)
#  define TRACE_SZT(NAME, X) TRACE_VAL(NAME, "%zu", (size_t)X)
#  define TRACE_PTR(NAME, X) TRACE_VAL(NAME, "%p", (void *)X)

#  define TRACE_INT2(X) TRACE_VAL("\b", "%d", X)
#  define TRACE_UIN2(X) TRACE_VAL("\b", "%u", (unsigned int)X)
#  define TRACE_LNG2(X) TRACE_VAL("\b", "%ld", (long)X)
#  define TRACE_ULN2(X) TRACE_VAL("\b", "%lu", (unsigned long)X)
#  define TRACE_DBL2(X) TRACE_VAL("\b", "%f", X)
#  define TRACE_SZT2(X) TRACE_VAL("\b", "%zu", (size_t)X)
#  define TRACE_PTR2(X) TRACE_VAL("\b", "%p", (void *)X)

# else

#  define PTRACE ;
#  define TRACE(N) 0

#  define TRACE_CLL(NAME, ...) NAME(__VA_ARGS__)

#  define TRACE_INT(NAME, X) X
#  define TRACE_UIN(NAME, X) (unsigned int)X
#  define TRACE_LNG(NAME, X) (long)X
#  define TRACE_ULN(NAME, X) (unsigned long)X
#  define TRACE_DBL(NAME, X) X
#  define TRACE_SZT(NAME, X) (size_t)X
#  define TRACE_PTR(NAME, X) (void *)X

#  define TRACE_INT2(X) X
#  define TRACE_UIN2(X) (unsigned int)X
#  define TRACE_LNG2(X) (long)X
#  define TRACE_ULN2(X) (unsigned long)X
#  define TRACE_DBL2(X) X
#  define TRACE_SZT2(X) (size_t)X
#  define TRACE_PTR2(X) (void *)X

# endif
#endif
