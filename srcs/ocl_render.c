/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 22:08:53 by jhache            #+#    #+#             */
/*   Updated: 2018/05/28 23:00:00 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "image.h"
#include "ocl_data.h"

void				compute_a_frame(t_rt *core);
cl_mem				ocl_set_kernel_arg(t_rt *core);

cl_mem				ocl_set_kernel_arg(t_rt *core)
{
	cl_int			ret;
	cl_mem			tmp[4];
	cl_image_format	format = {CL_RGBA, CL_UNSIGNED_INT8};
	cl_image_desc	desc = {CL_MEM_OBJECT_IMAGE2D, core->frame->w, core->frame->h, 1, 1, 0, 0, 0, 0, NULL};

	tmp[0] = clCreateImage(core->ocl.context, CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, &format, &desc, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (NULL);
	tmp[1] = clCreateBuffer(core->ocl.context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(t_cam), &core->scene.cam, &ret);
	if (ret != CL_SUCCESS)
	{
		clreleaseMemObject(tmp[0]);
		return (NULL);
	}
	tmp[2] = clCreateBuffer(core->ocl.context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(t_obj) * core->scene.objs_num, core->scene.objs, &ret);
	if (ret != CL_SUCCESS)
	{
		clreleaseMemObject(tmp[0]);
		clreleaseMemObject(tmp[1]);
		return (NULL);
	}
	tmp[3] = clCreateBuffer(core->ocl.context, CL_MEM_READ_WRITE | CL_MEM_ALLOC_HOST_PTR, sizeof(t_light) * core->scene.lights_num, core->scene.lights, &ret);
	if (ret != CL_SUCCESS)
	{
		clreleaseMemObject(tmp[0]);
		clreleaseMemObject(tmp[1]);
		clreleaseMemObject(tmp[2]);
		return (NULL);
	}
	ret = clSetKernelArg(core->ocl.kernel, 0, sizeof(cl_mem), &tmp[0]);
	ret |= clSetKernelArg(core->ocl.kernel, 1, sizeof(cl_mem), &tmp[1]);
	ret |= clSetKernelArg(core->ocl.kernel, 2, sizeof(cl_mem), &tmp[2]);
	ret |= clSetKernelArg(core->ocl.kernel, 3, sizeof(cl_mem), &tmp[3]);
	ret |= clSetKernelArg(core->ocl.kernel, 4, sizeof(size_t), &core->scene.objs_num);
	ret |= clSetKernelArg(core->ocl.kernel, 5, sizeof(size_t), &core->scene.lights_num);
	ret |= clSetKernelArg(core->ocl.kernel, 6, sizeof(cl_uint), &core->frame.w);
	ret |= clSetKernelArg(core->ocl.kernel, 7, sizeof(cl_uint), &core->frame.h);
//	ret |= clSetKernelArg(core->ocl.kernel, 6, sizeof(cl_uint), &core->scene.bg_color);
	if (ret != CL_SUCCESS)
		return (NULL);
	return (tmp[0]);
}

void				render_frame(t_rt *core)
{
	cl_mem			tmp;
	size_t			work_dim[3];

	tmp = ocl_set_kernel_arg(core);
	work_dim[0] = core->frame->w;
	work_dim[1] = core->frame->h;
	work_dim[2] = 1;
	clEnqueueNDRangeKernel(core->ocl.queue, core->ocl.kernel, 2, NULL, work_dim, NULL, 0, NULL, NULL);
	size_t	aa[] = {0, 0, 0};//on ne peut pas mettre NULL a la place
	clEnqueueReadImage(core->ocl.queue, tmp, CL_TRUE, aa,
			work_dim, 0, 0, core->frame->data, 0, NULL, NULL);
}
