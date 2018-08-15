/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_stack_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 15:11:44 by jhache            #+#    #+#             */
/*   Updated: 2018/08/15 18:28:02 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <libft_base/io.h>
#include <libft_base/memory.h>
#include "rt.h"

void				update_frame_size(t_rt *core, t_mem_info *mem_info)
{
	core->sdl.frame_width = core->sdl.win_width
		- core->sdl.win_width % mem_info->wg_dim[0];
	core->sdl.frame_height = core->sdl.win_height
		- core->sdl.win_height % mem_info->wg_dim[1];
	mem_info->wg_nb[0] = core->sdl.frame_width / mem_info->wg_dim[0];
	mem_info->wg_nb[1] = core->sdl.frame_height / mem_info->wg_dim[1];
}

cl_int				compute_work_size(t_mem_info *mem_info, t_rt *core)
{
	size_t			tmp;

	mem_info->wg_dim[0] = mem_info->buffer_size
		/ (size_t)(core->scene.depth + 1);
	tmp = mem_info->wg_dim[0] % mem_info->wg_mult;
	if (mem_info->wg_dim[0] == 0)
	{
		ft_putendl("error: the work group size is too small.");
		return (!CL_SUCCESS);
	}
	else if (tmp < mem_info->wg_dim[0])
		mem_info->wg_dim[0] -= tmp;
	mem_info->wg_dim[1] = 1;
	while (mem_info->wg_dim[0] > mem_info->wg_dim[1])
	{
		if (mem_info->wg_dim[0] % 2 == 1)
			break ;
		mem_info->wg_dim[0] >>= 1;
		mem_info->wg_dim[1] <<= 1;
	}
	printf("%zd x %zd\n", mem_info->wg_dim[0], mem_info->wg_dim[1]);
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
	return (ret);
}

cl_int				create_ocl_stack(t_rt *core, t_mem_info *mem_info)
{
	size_t			tmp;
	cl_int			ret;

	ft_bzero(mem_info->wg_dim, sizeof(size_t) * 3);
	ret = clGetDeviceInfo(core->ocl.device, CL_DEVICE_MAX_COMPUTE_UNITS,
			sizeof(cl_uint), &mem_info->compute_units, NULL);
	ret |= clGetKernelWorkGroupInfo(core->ocl.kernel, NULL,
			CL_KERNEL_PREFERRED_WORK_GROUP_SIZE_MULTIPLE,
			sizeof(size_t), &mem_info->wg_mult, NULL);
	ret |= clGetDeviceInfo(core->ocl.device, CL_DEVICE_LOCAL_MEM_SIZE,
			sizeof(cl_ulong), &mem_info->buffer_size, NULL);
	mem_info->buffer_size -= mem_info->used_local_mem;
	ret |= clGetKernelWorkGroupInfo(core->ocl.kernel, NULL,
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t), &tmp, NULL);
	if (ret != CL_SUCCESS)
	{
		ft_putendl("error while getting device memory infos.");
		return (ret);
	}
	mem_info->buffer_size /= sizeof(t_ray);
	mem_info->buffer_size -= mem_info->buffer_size % mem_info->wg_mult;
	if (mem_info->buffer_size > tmp)
		mem_info->buffer_size = tmp;
	return (stack_to_kernel(core, mem_info));
}
