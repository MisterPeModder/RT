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
	if (args->arg5 != NULL)
		clReleaseMemObject(args->arg5);
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
	result->arg5 = NULL;
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
	ret |= clSetKernelArg(core->ocl.kernel, 12, sizeof(cl_mem), &tmp->arg11);
	return ((ret != CL_SUCCESS) ? release_kernel_arg(tmp) : tmp);
}

static t_kargs		*ocl_set_kernel_arg(t_rt *core, cl_int *ret)
{
	t_kargs			*tmp;
	static t_clint	hash[256] = {208, 34, 231, 213, 32, 248, 233, 56, 161, 78, 24, 140, 71, 48, 140, 
		254, 245, 255, 247, 247, 40, 185, 248, 251, 245, 28, 124, 204, 204, 76, 36, 1, 107, 28, 234, 
		163, 202, 224, 245, 128, 167, 204, 9, 92, 217, 54, 239, 174, 173, 102, 193, 189, 190, 121, 
		100, 108, 167, 44, 43, 77, 180, 204, 8, 81, 70, 223, 11, 38, 24, 254, 210, 210, 177, 32, 81, 
		195, 243, 125, 8, 169, 112, 32, 97, 53, 195, 13, 203, 9, 47, 104, 125, 117, 114, 124, 165, 
		203, 181, 235, 193, 206, 70, 180, 174, 0, 167, 181, 41, 164, 30, 116, 127, 198, 245, 146, 
		87, 224, 149, 206, 57, 4, 192, 210, 65, 210, 129, 240, 178, 105, 228, 108, 245, 148, 140, 
		40, 35, 195, 38, 58, 65, 207, 215, 253, 65, 85, 208, 76, 62, 3, 237, 55, 89, 232, 50, 217, 
		64, 244, 157, 199, 121, 252, 90, 17, 212, 203, 149, 152, 140, 187, 234, 177, 73, 174, 
		193, 100, 192, 143, 97, 53, 145, 135, 19, 103, 13, 90, 135, 151, 199, 91, 239, 247, 33, 
		39, 145, 101, 120, 99, 3, 186, 86, 99, 41, 237, 203, 111, 79, 220, 135, 158, 42, 30, 154, 
		120, 67, 87, 167, 135, 176, 183, 191, 253, 115, 184, 21, 233, 58, 129, 233, 142, 39, 128, 
		211, 118, 137, 139, 255, 114, 20, 218, 113, 154, 27, 127, 246, 250, 1, 8, 198, 250, 209, 
		92, 222, 173, 21, 88, 102, 219};

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
	tmp->arg5 = clCreateBuffer(core->ocl.context,
			CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
			sizeof(t_clint) * 256, hash, ret);
	if (*ret != CL_SUCCESS)
		return (release_kernel_arg(tmp));
	*ret = clSetKernelArg(core->ocl.kernel, 1, sizeof(cl_mem), &tmp->arg2);
	*ret |= clSetKernelArg(core->ocl.kernel, 2, sizeof(cl_mem), &tmp->arg3);
	*ret |= clSetKernelArg(core->ocl.kernel, 3, sizeof(cl_mem), &tmp->arg4);
	*ret |= clSetKernelArg(core->ocl.kernel, 9,
			sizeof(t_clint), &core->scene.depth);
	*ret |= clSetKernelArg(core->ocl.kernel, 11, sizeof(cl_mem), &tmp->arg5);
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
