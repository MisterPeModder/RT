/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/16 00:31:25 by jhache            #+#    #+#             */
/*   Updated: 2018/08/16 00:47:41 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <libft_base/memory.h>
#include "rt.h"
#include "image.h"
#include "ocl_data.h"

cl_int				ocl_set_kernel_arg(t_rt *core)
{
	cl_int			ret;

	if (core->mem_objects->arg1 != NULL)
		clReleaseMemObject(core->mem_objects->arg1);
	core->mem_objects->arg1 = clCreateBuffer(core->ocl.context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_cam), &core->scene.cam, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	ret = clSetKernelArg(core->ocl.kernel, 1, sizeof(cl_mem),
			&core->mem_objects->arg1);
	ret |= clSetKernelArg(core->ocl.kernel, 9,
			sizeof(t_clint), &core->scene.depth);
	return (ret);
}

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
	ret |= clSetKernelArg(ocl->kernel, 6, sizeof(cl_uint),
			&core->sdl.frame_width);
	ret |= clSetKernelArg(ocl->kernel, 7, sizeof(cl_uint),
			&core->sdl.frame_height);
	return (ret);
}

static cl_int		load_arg_to_kernel(t_ocl *ocl, t_rt *core)
{
	cl_int			ret;
	char			no_negative;

	no_negative = core->state_flags & SF_NO_NEGATIVE;
	ret = clSetKernelArg(core->ocl.kernel, 2, sizeof(cl_mem),
			&core->mem_objects->arg2);
	ret |= clSetKernelArg(core->ocl.kernel, 3, sizeof(cl_mem),
			&core->mem_objects->arg3);
	ret |= clSetKernelArg(core->ocl.kernel, 11, sizeof(cl_mem),
			&core->mem_objects->arg11);
	ret |= clSetKernelArg(ocl->kernel, 4, sizeof(unsigned int),
			&core->scene.objs_num);
	ret |= clSetKernelArg(ocl->kernel, 5, sizeof(unsigned int),
			&core->scene.lights_num);
	ret |= clSetKernelArg(core->ocl.kernel, 10, sizeof(char), &no_negative);
	ret |= clSetKernelArg(ocl->kernel, 13,
		sizeof(t_object) * core->scene.objs_num, NULL);
	core->mem_info.used_local_mem += sizeof(t_object) * core->scene.objs_num;
	return (ret);
}

static cl_int		init_kernel_args(t_ocl *ocl, t_rt *core)
{
	cl_int			ret;

	if ((core->mem_objects = ft_memalloc(sizeof(t_kargs))) == NULL)
		return (!CL_SUCCESS);
	core->mem_objects->arg11 = clCreateBuffer(core->ocl.context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_mesh_triangle) * core->scene.triangles_num,
			core->scene.mesh_triangles, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	core->mem_objects->arg3 = clCreateBuffer(core->ocl.context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * core->scene.lights_num, core->scene.lights, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	core->mem_objects->arg2 = clCreateBuffer(core->ocl.context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * core->scene.objs_num, core->scene.objs, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	ret = load_arg_to_kernel(ocl, core);
	return (ret);
}

cl_int				load_first_kernel_args(t_rt *core)
{
	cl_int			ret;

	if ((ret = init_kernel_args(&core->ocl, core)) != CL_SUCCESS)
	{
		ft_putendl("error while loading fixed kernel arguments.");
		return (ret);
	}
	if ((ret = create_ocl_stack(core, &core->mem_info)) != CL_SUCCESS
		|| (ret = compute_work_size(&core->mem_info, core)) != CL_SUCCESS)
	{
		ft_putendl("error while creating the openCL stack.");
		return (ret);
	}
	if ((ret = init_frame_kernel_arg(&core->ocl, core)) != CL_SUCCESS)
		ft_putendl("error while loading frame kernel arguments.");
	return (ret);
}
