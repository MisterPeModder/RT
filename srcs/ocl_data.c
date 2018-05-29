/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:01:49 by jhache            #+#    #+#             */
/*   Updated: 2018/05/29 05:25:38 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_data.h"
#include <unistd.h>
#include <libft_base/io.h>
#include <libft_base/memory.h>

static void	ocl_set_to_null(t_ocl *ocl)
{
	ocl->platform = NULL;
	ocl->device = NULL;
	ocl->context = NULL;
	ocl->queue = NULL;
	ocl->program = NULL;
	ocl->kernel = NULL;
}

cl_int		ocl_release(t_ocl *ocl, const char *debug_msg, cl_int ret)
{
	int	i;

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

#include <stdio.h>

static void		print_build_log(t_ocl *ocl)
{
	char		log[8192];
	size_t		size;
	cl_int		ret;

	ret = clGetProgramBuildInfo(ocl->program, ocl->device, CL_PROGRAM_BUILD_LOG,
			8192, log, &size);
	if (size == 0 || size > 8192)
		ft_putendl("couldn't fetch openCL kernel build log.");
	else
		write(STDERR_FILENO, log, size);
}

cl_int		ft_create_kernel(t_ocl *ocl)
{
	cl_int	ret;
	char	**src;
	size_t	count;

	ft_putendl("reading program source...");
	if ((src = read_src_file(KERNEL_PATH, &count)) == NULL)
		return (-1);
	ft_putendl("read program source");
	ocl->program = clCreateProgramWithSource(ocl->context, count,
			(const char **)src, NULL, &ret);
	ft_putendl("created openCL program");
	free_strtab(src, count);
	if (ocl->program == NULL || ret < 0)
	{
		ft_putendl("error while creating program.");
		return (ret < 0 ? ret : -1);
	}
	ft_putendl("building with " OPENCL_BUILD_FLAGS);
	if ((ret = clBuildProgram(ocl->program, 1,
					&ocl->device, OPENCL_BUILD_FLAGS, NULL, NULL)) < 0)
	{
		ft_putendl("error while building program:");
		print_build_log(ocl);
		return (ret);
	}
	ft_putendl("built openCL program");
	if ((ret = clCreateKernelsInProgram(ocl->program,
					1, &ocl->kernel, NULL)) < 0)
		ft_putendl("error while creating kernels.");
	return (ret < 0 ? ret : 0);
}

cl_int		ocl_init(t_ocl *ocl)
{
	cl_int	ret;

	ft_putendl("starting openCL init...");
	ocl_set_to_null(ocl);
	ret = clGetPlatformIDs(1, &ocl->platform, NULL);
	ft_putendl("got platform ID");
	if (ret < 0)
		return (ocl_release(ocl, "error while getting platform data.", ret));
	ret = clGetDeviceIDs(ocl->platform, CL_DEVICE_TYPE_GPU, 1,
			&ocl->device, NULL);
	ft_putendl("got device IDs");
	if (ret < 0)
		return (ocl_release(ocl, "error while getting device data.", ret));
	ocl->context = clCreateContext(NULL, 1, &ocl->device, NULL, NULL, &ret);
	ft_putendl("created context");
	if (ret < 0)
		return (ocl_release(ocl, "error while creating a context.", ret));
	ocl->queue = clCreateCommandQueue(ocl->context, ocl->device, 0, &ret);
	ft_putendl("created command queue");
	if (ret < 0)
		return (ocl_release(ocl, "error while creating a queue.", ret));
	if ((ret = ft_create_kernel(ocl)) < 0)
		return (ocl_release(ocl, NULL, ret));
	return (0);
}
