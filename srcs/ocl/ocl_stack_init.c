/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_stack_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:11:44 by jhache            #+#    #+#             */
/*   Updated: 2018/06/25 21:08:42 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <libft_base/io.h>
#include <libft_base/memory.h>
#include "rt.h"
#include "ocl_data.h"
#include "ocl_common_structs.h"
#include <stdio.h>
void				update_frame_size(t_rt *core, t_mem_info *mem_info)
{
	core->sdl.frame_width = core->sdl.win_width
		- core->sdl.win_width % mem_info->dim[0];
	core->sdl.frame_height = core->sdl.win_height
		- core->sdl.win_height % mem_info->dim[1];
	printf("%zd x %zd\n", mem_info->dim[0], mem_info->dim[1]);
}

cl_int				compute_work_size(t_mem_info *mem_info, t_rt *core)
{
	mem_info->dim[0] = mem_info->buffer_size / (size_t)(core->scene.depth + 1);
	mem_info->dim[0] -= mem_info->dim[0] % mem_info->wg_mult;
	mem_info->dim[1] = 1;
	if (mem_info->dim[0] == 0)
	{
		ft_putendl("error: the work group size is too small.");
		return (!CL_SUCCESS);
	}
	while (mem_info->dim[0] > mem_info->dim[1])
	{
		if (mem_info->dim[0] % 2 == 1)
			break ;
		mem_info->dim[0] >>= 1;
		mem_info->dim[1] <<= 1;
	}
	update_frame_size(core, mem_info);
	return (CL_SUCCESS);
}

static cl_int		stack_to_kernel(t_rt *core, t_mem_info *mem_info)
{
	cl_int			ret;
	int				i;

	ret = !CL_SUCCESS;
	i = 0;
	while (i < 4 && ret != CL_SUCCESS)
	{
		ret = clSetKernelArg(core->ocl.kernel, 8,
		sizeof(t_ray) * mem_info->buffer_size, NULL);
		if (ret == CL_SUCCESS)
			break ;
		mem_info->buffer_size = (size_t)((float)mem_info->buffer_size / 2);
		mem_info->buffer_size -= mem_info->buffer_size % mem_info->wg_mult;
		++i;
	}
	printf("i = %d\nnb d'elem dans la stack: %zd\n", i, mem_info->buffer_size);
	return (ret);
}

cl_int				create_ocl_stack(t_rt *core, t_mem_info *mem_info)
{
	size_t			max_wg_size;
	cl_int			ret;
//
	cl_uint	tmp;
	ft_bzero(mem_info->dim, sizeof(size_t) * 3);
	clGetDeviceInfo(core->ocl.device, CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &tmp, NULL);
	printf("max compute units: %u\n", tmp);
//
	ret = clGetKernelWorkGroupInfo(core->ocl.kernel, NULL,
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &max_wg_size, NULL);
	ret |= clGetKernelWorkGroupInfo(core->ocl.kernel, NULL,
			CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,
			sizeof(size_t), &mem_info->wg_mult, NULL);
	ret |= clGetDeviceInfo(core->ocl.device, CL_DEVICE_LOCAL_MEM_SIZE,
			sizeof(cl_ulong), &mem_info->buffer_size, NULL);
	if (ret != CL_SUCCESS)
	{
		ft_putendl("error while getting device memory infos.");
		return (ret);
	}
	mem_info->buffer_size /= sizeof(t_ray);
	mem_info->buffer_size -= mem_info->buffer_size % mem_info->wg_mult;
	if (mem_info->buffer_size > max_wg_size)
		mem_info->buffer_size = max_wg_size;
	return (stack_to_kernel(core, mem_info));
}
