/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:01:49 by jhache            #+#    #+#             */
/*   Updated: 2018/06/28 17:02:50 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <unistd.h>
#include <libft_base/io.h>
#include <libft_base/memory.h>

static void			ocl_set_to_null(t_ocl *ocl)
{
	ocl->platform = NULL;
	ocl->device = NULL;
	ocl->context = NULL;
	ocl->queue = NULL;
	ocl->program = NULL;
	ocl->kernel = NULL;
}

cl_int				ocl_release(t_ocl *ocl, const char *debug_msg, cl_int ret)
{
	int				i;

	i = 0;
	if (ocl->device != NULL)
		clReleaseDevice(ocl->device);
	if (ocl->context != NULL)
		clReleaseContext(ocl->context);
	if (ocl->program != NULL)
		clReleaseProgram(ocl->program);
	if (ocl->kernel != NULL)
		clReleaseKernel(ocl->kernel);
	if (ocl->queue != NULL)
		clReleaseCommandQueue(ocl->queue);
	if (debug_msg != NULL)
		ft_putendl(debug_msg);
	ocl_set_to_null(ocl);
	return (ret);
}

static void			print_build_log(t_ocl *ocl)
{
	char			*log;
	size_t			size;
	cl_int			ret;

	ret = clGetProgramBuildInfo(ocl->program, ocl->device, CL_PROGRAM_BUILD_LOG,
			0, NULL, &size);
	if (ret != CL_SUCCESS || (log = malloc(sizeof(char) * size)) == NULL)
	{
		ft_putendl("couldn't fetch openCL kernel build log.");
		return ;
	}
	ret = clGetProgramBuildInfo(ocl->program, ocl->device, CL_PROGRAM_BUILD_LOG,
			size, log, NULL);
	if (ret != CL_SUCCESS)
		ft_putendl("couldn't fetch openCL kernel build log.");
	else
		write(STDERR_FILENO, log, size);
}

static cl_int		create_kernel(t_ocl *ocl)
{
	cl_int			ret;
	char			**src;
	size_t			count;

	if ((src = read_src_file(KERNEL_PATH, &count)) == NULL)
		return (-1);
	ocl->program = clCreateProgramWithSource(ocl->context, count,
			(const char **)src, NULL, &ret);
	free_strtab(src, count);
	if (ocl->program == NULL || ret < 0)
	{
		ft_putendl("error while creating program.");
		return (ret < 0 ? ret : -1);
	}
	if ((ret = clBuildProgram(ocl->program, 1,
					&ocl->device, OPENCL_BUILD_FLAGS, NULL, NULL)) < 0)
	{
		ft_putendl("error while building program:");
		print_build_log(ocl);
		return (ret);
	}
	if ((ret = clCreateKernelsInProgram(ocl->program,
					1, &ocl->kernel, NULL)) < 0)
		ft_putendl("error while creating kernels.");
	return (ret < 0 ? ret : 0);
}

cl_int				ocl_init(t_ocl *ocl)
{
	cl_int			ret;

	ocl_set_to_null(ocl);
	ret = clGetPlatformIDs(1, &ocl->platform, NULL);
	if (ret != CL_SUCCESS)
		return (ocl_release(ocl, "error while getting platform data.", ret));
	ret = clGetDeviceIDs(ocl->platform, CL_DEVICE_TYPE_GPU, 1,
			&ocl->device, NULL);
	if (ret != CL_SUCCESS)
		return (ocl_release(ocl, "error while getting device data.", ret));
	ocl->context = clCreateContext(NULL, 1, &ocl->device, NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ocl_release(ocl, "error while creating a context.", ret));
	ocl->queue = clCreateCommandQueue(ocl->context, ocl->device, 0, &ret);
	if (ret != CL_SUCCESS)
		return (ocl_release(ocl, "error while creating a queue.", ret));
	if ((ret = create_kernel(ocl)) != CL_SUCCESS)
		return (ocl_release(ocl, NULL, ret));
	return (CL_SUCCESS);
}
