/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:01:49 by jhache            #+#    #+#             */
/*   Updated: 2018/05/26 19:07:09 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ocl_data.h"
#include <libft_base/io.h>

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

cl_int		ft_create_kernel(t_ocl *ocl, const char *path, size_t len)
{
	cl_int	ret[2];

	ocl->program = clCreateProgramWithBinary(
			ocl->context, 1, &ocl->device,
			&len, (const unsigned char **)&path, ret, &ret[1]);
	if (ocl->program == NULL || ret[0] < 0 || ret[1] < 0)
	{
		ft_putendl("error while creating program.");
		return (-1);
	}
	if ((ret[0] = clBuildProgram(ocl->program, 1,
				&ocl->device, OPENCL_BUILD_FLAGS, NULL, NULL)) < 0)
	{
		ft_putendl("error while building program.");
		return (ret[0]);
	}
	if ((ret[0] = clCreateKernelsInProgram(ocl->program,
					1, &ocl->kernel, NULL)) < 0)
		ft_putendl("error while creating kernels.");
	return (ret[0]);
}

cl_int		ocl_init(t_ocl *ocl)
{
	cl_int	ret;

	ocl_set_to_null(ocl);
	ret = clGetPlatformIDs(1, &ocl->platform, NULL);
	if (ret < 0)
		return (ocl_release(ocl, "error while getting platform data.", ret));
	ret = clGetDeviceIDs(ocl->platform, CL_DEVICE_TYPE_GPU, 1,
			&ocl->device, NULL);
	if (ret < 0)
		return (ocl_release(ocl, "error while getting device data.", ret));
	ocl->context = clCreateContext(NULL, 1, &ocl->device, NULL, NULL, &ret);
	if (ret < 0)
		return (ocl_release(ocl, "error while creating a context.", ret));
	ocl->queue = clCreateCommandQueue(ocl->context, ocl->device, 0, &ret);
	if (ret < 0)
		return (ocl_release(ocl, "error while creating a queue.", ret));
	return (0);
}
