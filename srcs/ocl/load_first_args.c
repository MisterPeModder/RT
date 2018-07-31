/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_first_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 14:50:11 by jhache            #+#    #+#             */
/*   Updated: 2018/07/31 02:11:41 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include "rt.h"
#include "image.h"
#include "ocl_data.h"
#include <stdio.h>

cl_int				init_frame_kernel_arg(t_ocl *ocl, t_rt *core)
{
	cl_image_format	form;
	cl_image_desc	des;
	cl_int			ret;

	form = (cl_image_format){.image_channel_order = CL_RGBA,
		.image_channel_data_type = CL_UNSIGNED_INT8};
	des = (cl_image_desc){.image_type = CL_MEM_OBJECT_IMAGE2D,
		.image_width = core->sdl.frame_width,
		.image_height = core->sdl.frame_height, .image_depth = 1,
		.image_array_size = 1, .image_row_pitch = 0, .image_slice_pitch = 0,
		.num_mip_levels = 0, .num_samples = 0, .buffer = NULL};
	ocl->ocl_img = clCreateImage(core->ocl.context,
			CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, &form, &des, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	ret = clSetKernelArg(core->ocl.kernel, 0, sizeof(cl_mem), &ocl->ocl_img);
	return (ret);
}

cl_int				init_kernel_args(t_ocl *ocl, t_rt *core)
{
	cl_int			ret;

	ret = init_frame_kernel_arg(ocl, core);
	ret |= clSetKernelArg(ocl->kernel, 4, sizeof(unsigned int), &core->scene.objs_num);
	ret |= clSetKernelArg(ocl->kernel, 5, sizeof(unsigned int),
			&core->scene.lights_num);
	ret |= clSetKernelArg(ocl->kernel, 6, sizeof(cl_uint),
			&core->sdl.frame_width);
	ret |= clSetKernelArg(ocl->kernel, 7, sizeof(cl_uint),
			&core->sdl.frame_height);
	return (ret);
}

cl_int				load_first_kernel_args(t_rt *core)
{
	cl_int			ret;

	if ((ret = create_ocl_stack(core, &core->mem_info)) != CL_SUCCESS)
	{
		ft_putendl("error while creating the openCL stack.");
		return (ret);
	}
	if ((ret = compute_work_size(&core->mem_info, core)) != CL_SUCCESS
		|| (ret = init_kernel_args(&core->ocl, core)) != CL_SUCCESS)
	{
		ft_putendl("error while loading fixed kernel arguments.");
		return (ret);
	}
	return (ret);
}
