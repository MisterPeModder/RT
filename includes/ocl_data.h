/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:08:48 by jhache            #+#    #+#             */
/*   Updated: 2018/05/26 19:05:50 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_DATA_H
# define OCL_DATA_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

/*
** program building's flags :
*/
# define OPENCL_BUILD_FLAGS "-Werror"


/*
** definition of the t_ocl struct, which contain data for openCL functions.
*/
typedef struct			s_opencl_data
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
}						t_ocl;


cl_int					ocl_release(t_ocl *ocl, const char *debug_msg,
									cl_int ret);
cl_int					ft_create_kernel(t_ocl *ocl, const char *path,
									size_t len);
cl_int					ocl_init(t_ocl *ocl);
#endif
