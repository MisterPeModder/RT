/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/26 14:01:49 by jhache            #+#    #+#             */
/*   Updated: 2018/05/31 17:49:16 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <unistd.h>
#include <libft_base/io.h>
#include <libft_base/memory.h>

static void		ocl_set_to_null(t_ocl *ocl)
{
	ocl->platform = NULL;
	ocl->device = NULL;
	ocl->context = NULL;
	ocl->queue = NULL;
	ocl->program = NULL;
	ocl->kernel = NULL;
}

cl_int			ocl_release(t_ocl *ocl, const char *debug_msg, cl_int ret)
{
	int			i;

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

static void		print_build_log(t_ocl *ocl)
{
	char		*log;
	size_t		size;
	cl_int		ret;

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

static cl_int		init_kernel_args(t_ocl *ocl, t_rt *core)
{
	cl_int			ret;
	cl_image_format	form;
	cl_image_desc	des;

	form = (cl_image_format){.image_channel_order = CL_RGBA,
		.image_channel_data_type = CL_UNSIGNED_INT8};
	des = (cl_image_desc){.image_type = CL_MEM_OBJECT_IMAGE2D,
		.image_width = core->frame->w, .image_height = core->frame->h,
		.image_depth = 1, .image_array_size = 1, .image_row_pitch = 0,
		.image_slice_pitch = 0, .num_mip_levels = 0, .num_samples = 0,
		.buffer = NULL};
	ocl->ocl_img = clCreateImage(core->ocl.context,
			CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, &form, &des, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	ret = clSetKernelArg(ocl->kernel, 4, sizeof(size_t), &core->scene.objs_num);
	ret |= clSetKernelArg(ocl->kernel, 5, sizeof(size_t),
			&core->scene.lights_num);
	ret |= clSetKernelArg(ocl->kernel, 6, sizeof(cl_uint), &core->frame->w);
	ret |= clSetKernelArg(ocl->kernel, 7, sizeof(cl_uint), &core->frame->h);
/*	ret |= clSetKernelArg(core->ocl.kernel, 6, sizeof(cl_uint),
			&core->scene.bg_color);*/
	ret |= clSetKernelArg(core->ocl.kernel, 0, sizeof(cl_mem), &ocl->ocl_img);
	return (ret);
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

cl_int			ocl_init(t_ocl *ocl, t_rt *core)
{
	cl_int		ret;

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
	if ((ret = create_kernel(ocl)) != CL_SUCCESS ||
			init_kernel_args(ocl, core) != CL_SUCCESS)
		return (ocl_release(ocl, NULL, ret));
	return (0);
}
