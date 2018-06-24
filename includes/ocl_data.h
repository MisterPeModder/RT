/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_data.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:08:48 by jhache            #+#    #+#             */
/*   Updated: 2018/06/23 20:25:27 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCL_DATA_H
# define OCL_DATA_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# ifndef KERNEL_PATH
#  error "KERNEL_PATH not specified"
# endif

/*
** program building's flags :
*/
# ifndef OPENCL_BUILD_FLAGS
#  error "OPENCL_BUILD_FLAGS not specified"
# endif

# define BUFF_SIZE 128
# define TAB_STEP_SIZE 10

/*
** definition of the t_ocl struct, which contain data for openCL functions.
*/
typedef struct			s_ocl
{
	cl_platform_id		platform;
	cl_device_id		device;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_mem				ocl_img;
}						t_ocl;

struct s_rt;

typedef struct			s_kargs
{
	cl_mem				arg1;
	cl_mem				arg2;
	cl_mem				arg3;
	cl_mem				arg4;
}						t_kargs;

/*
** OpenCL creation and destruction functions :
*/
cl_int					ocl_init(t_ocl *ocl, struct s_rt *core);
cl_int					init_kernel_args(t_ocl *ocl, struct s_rt *core);
cl_int					ft_create_kernel(t_ocl *ocl);
cl_int					ocl_release(t_ocl *ocl, const char *debug_msg,
		cl_int ret);

/*
** Functions for reading the kernel :
*/
void					*free_strtab(char **tab, size_t size);
char					**read_src_file(const char *file_name, size_t *size);

#endif
