/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:58:10 by yguaye            #+#    #+#             */
/*   Updated: 2018/05/29 03:39:38 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_TYPES_H
# define OCL_TYPES_H

# ifdef __OPENCL_C_VERSION__
#  define IS_OPENCL 1
# else
#  define IS_OPENCL 0
# endif

# if IS_OPENCL == 1
#  include "internal_ocl_types_cl.h"
# else
#  include "internal_ocl_types_c.h"
# endif

#endif
