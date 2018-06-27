/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_ocl_types_c.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguaye <yguaye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 16:58:56 by yguaye            #+#    #+#             */
/*   Updated: 2018/06/23 16:10:34 by jloro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_OCL_TYPES_C_H
# define INTERNAL_OCL_TYPES_C_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

typedef cl_bool			t_clbool;
typedef cl_char			t_clchar;
typedef cl_uchar		t_cluchar;
typedef cl_int			t_clint;
typedef cl_uint			t_cluint;
typedef cl_long			t_cllong;
typedef cl_ulong		t_clulong;
typedef cl_float		t_clfloat;
typedef cl_float3		t_clfloat3;
typedef cl_int3			t_clint3;
#endif
