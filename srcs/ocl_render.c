/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 22:08:53 by jhache            #+#    #+#             */
/*   Updated: 2018/05/27 22:11:24 by jhache           ###   ########.fr       */
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
	cl_mem			tmp;
	cl_image_format	a = {CL_RGBA, CL_SIGNED_INT8};
	cl_image_desc	b = {CL_MEM_OBJECT_IMAGE2D, core->frame->w, core->frame->h, 1, 1, 0, 0, 0, 0, NULL};

	tmp = clCreateImage(core->ocl.context, CL_MEM_WRITE_ONLY | CL_MEM_ALLOC_HOST_PTR,
			&a, &b,
			NULL, &ret);
	if (ret != CL_SUCCESS)
		return (NULL);
	ret = clSetKernelArg(core->ocl.kernel, 0, sizeof(cl_uint), &core->frame->w);
	ret |= clSetKernelArg(core->ocl.kernel, 1, sizeof(cl_uint), &core->frame->h);
	ret |= clSetKernelArg(core->ocl.kernel, 2, sizeof(cl_mem), &tmp);
	if (ret != CL_SUCCESS)
		return (NULL);
	return (tmp);
}

void				compute_a_frame(t_rt *core)
{
	cl_mem			tmp;
	size_t			work_dim[3];

	tmp = ocl_set_kernel_arg(core);
	work_dim[0] = core->frame->w;
	work_dim[1] = core->frame->h;
	work_dim[2] = 1;
	clEnqueueNDRangeKernel(core->ocl.queue, core->ocl.kernel, 2, NULL, work_dim, NULL,0, NULL, NULL);
	size_t	aa[] = {0, 0, 0};//on ne peut pas mettre NULL a la place
	clEnqueueReadImage(core->ocl.queue, tmp, CL_TRUE, aa,
			work_dim, 0, 0, core->frame->data, 0, NULL, NULL);
}
