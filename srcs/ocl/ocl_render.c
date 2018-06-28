/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 22:08:53 by jhache            #+#    #+#             */
/*   Updated: 2018/06/28 16:30:08 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include <unistd.h>
#include "rt.h"
#include "image.h"
#include "ocl_data.h"

static void			*release_kernel_arg(t_kargs *args)
{
	if (args == NULL)
		return (NULL);
	if (args->arg1 != NULL)
		clReleaseMemObject(args->arg1);
	if (args->arg2 != NULL)
		clReleaseMemObject(args->arg2);
	if (args->arg3 != NULL)
		clReleaseMemObject(args->arg3);
	if (args->arg4 != NULL)
		clReleaseMemObject(args->arg4);
	if (args->arg9 != NULL)
		clReleaseMemObject(args->arg9);
	if (args->arg11 != NULL)
		clReleaseMemObject(args->arg9);
	free(args);
	return (NULL);
}

static t_kargs		*init_kargs(t_rt *core)
{
	t_kargs			*result;
	char			no_negative;

	result = malloc(sizeof(t_kargs));
	if (result == NULL)
		return (NULL);
	result->arg1 = NULL;
	result->arg2 = NULL;
	result->arg3 = NULL;
	result->arg4 = NULL;
	result->arg9 = NULL;
	result->arg11 = NULL;
	no_negative = core->state_flags & SF_NO_NEGATIVE;
	return (clSetKernelArg(core->ocl.kernel, 10, sizeof(char), &no_negative)
			== CL_SUCCESS ? result : NULL);
}

static t_kargs		*ocl_set_kernel_arg2(t_rt *core, t_kargs *tmp)
{
	cl_int			ret;

	tmp->arg11 = clCreateBuffer(core->ocl.context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_mesh_triangle) * core->scene.triangle_total_num,
			core->scene.mesh_triangle, &ret);
	if (ret != CL_SUCCESS)
		return (release_kernel_arg(tmp));
	ret |= clSetKernelArg(core->ocl.kernel, 11, sizeof(cl_mem), &tmp->arg11);
	return ((ret != CL_SUCCESS) ? release_kernel_arg(tmp) : tmp);
}

static t_kargs		*ocl_set_kernel_arg(t_rt *core, cl_int *ret)
{
	t_kargs			*tmp;

	if ((tmp = init_kargs(core)) == NULL)
		return (NULL);
	tmp->arg2 = clCreateBuffer(core->ocl.context, CL_MEM_READ_WRITE
			| CL_MEM_COPY_HOST_PTR, sizeof(t_cam), &core->scene.cam, ret);
	if (*ret != CL_SUCCESS)
		return (release_kernel_arg(tmp));
	tmp->arg3 = clCreateBuffer(core->ocl.context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_object) * core->scene.objs_num, core->scene.objs, ret);
	if (*ret != CL_SUCCESS)
		return (release_kernel_arg(tmp));
	tmp->arg4 = clCreateBuffer(core->ocl.context,
			CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR,
			sizeof(t_light) * core->scene.lights_num, core->scene.lights, ret);
	if (*ret != CL_SUCCESS)
		return (release_kernel_arg(tmp));
	*ret = clSetKernelArg(core->ocl.kernel, 1, sizeof(cl_mem), &tmp->arg2);
	*ret |= clSetKernelArg(core->ocl.kernel, 2, sizeof(cl_mem), &tmp->arg3);
	*ret |= clSetKernelArg(core->ocl.kernel, 3, sizeof(cl_mem), &tmp->arg4);
	*ret |= clSetKernelArg(core->ocl.kernel, 9,
			sizeof(t_clint), &core->scene.depth);
	return ((*ret != CL_SUCCESS) ? release_kernel_arg(tmp) :
			ocl_set_kernel_arg2(core, tmp));
}

cl_int				render_frame(t_rt *core)
{
	t_kargs			*tmp;
	size_t			glob_dim[3];
	cl_int			ret;
	size_t			offset[3];

	if ((tmp = ocl_set_kernel_arg(core, &ret)) == NULL)
		return (ret);
	update_frame_size(core, &core->mem_info);
	glob_dim[0] = core->sdl.frame_width;
	glob_dim[1] = core->sdl.frame_height;
	glob_dim[2] = 1;
	ret = clEnqueueNDRangeKernel(core->ocl.queue, core->ocl.kernel, 2, NULL,
			glob_dim, core->mem_info.dim, 0, NULL, NULL);
	if (ret != CL_SUCCESS && !release_kernel_arg(tmp))
		return (ret);
	ft_bzero(offset, sizeof(size_t) * 3);
	SDL_LockSurface(core->frame);
	ret = clEnqueueReadImage(core->ocl.queue, core->ocl.ocl_img, CL_TRUE,
			offset, glob_dim, 0, 0, core->frame->pixels, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
		return (ret);
	return (print_frame(core) + (int)release_kernel_arg(tmp) * 0);
}
