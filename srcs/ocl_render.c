/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 22:08:53 by jhache            #+#    #+#             */
/*   Updated: 2018/05/29 13:50:08 by yguaye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/io.h>
#include <unistd.h>
#include "rt.h"
#include "image.h"
#include "ocl_data.h"

static cl_mem		ocl_set_kernel_arg(t_rt *core)
{
	cl_int			ret;
	cl_mem			tmp[4];
	cl_image_format	format = {{CL_RGBA, CL_UNSIGNED_INT8}};
	cl_image_desc	desc = {CL_MEM_OBJECT_IMAGE2D, core->frame->w, core->frame->h, 1, 1, 0, 0, 0, 0, NULL};

	tmp[0] = clCreateImage(core->ocl.context, CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR, &format, &desc, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (NULL);
	tmp[1] = clCreateBuffer(core->ocl.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_cam), &core->scene.cam, &ret);
	if (ret != CL_SUCCESS)
	{
		clReleaseMemObject(tmp[0]);
		return (NULL);
	}
	tmp[2] = clCreateBuffer(core->ocl.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_object) * core->scene.objs_num, core->scene.objs, &ret);
	if (ret != CL_SUCCESS)
	{
		clReleaseMemObject(tmp[0]);
		clReleaseMemObject(tmp[1]);
		return (NULL);
	}
	tmp[3] = clCreateBuffer(core->ocl.context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_light) * core->scene.lights_num, core->scene.lights, &ret);
	if (ret != CL_SUCCESS)
	{
		ft_putendl("args creation: failure");
		clReleaseMemObject(tmp[0]);
		clReleaseMemObject(tmp[1]);
		clReleaseMemObject(tmp[2]);
		return (NULL);
	}
	ret = clSetKernelArg(core->ocl.kernel, 0, sizeof(cl_mem), tmp);
	ret |= clSetKernelArg(core->ocl.kernel, 1, sizeof(cl_mem), &tmp[1]);
	ret |= clSetKernelArg(core->ocl.kernel, 2, sizeof(cl_mem), &tmp[2]);
	ret |= clSetKernelArg(core->ocl.kernel, 3, sizeof(cl_mem), &tmp[3]);
	if (ret != CL_SUCCESS)
		return (NULL);
	return (tmp[0]);
}

void				render_frame(t_rt *core)
{
	cl_mem			tmp;
	size_t			work_dim[3];
	cl_int			ret;

	if (!(tmp = ocl_set_kernel_arg(core)))
	{
		ft_putendl_fd("\x1b[93mWARNING\x1b[0m: failed to render frame !!", STDERR_FILENO);
		return ;
	}
	work_dim[0] = core->frame->w;
	work_dim[1] = core->frame->h;
	work_dim[2] = 1;
	ret = clEnqueueNDRangeKernel(core->ocl.queue, core->ocl.kernel, 2, NULL, work_dim, NULL, 0, NULL, NULL);
	size_t	aa[] = {0, 0, 0};//on ne peut pas mettre NULL a la place
	ret = clEnqueueReadImage(core->ocl.queue, tmp, CL_TRUE, aa,
			work_dim, 0, 0, core->frame->data, 0, NULL, NULL);
}
