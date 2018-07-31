/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ocl_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <jhache@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/27 22:08:53 by jhache            #+#    #+#             */
/*   Updated: 2018/07/31 00:01:57 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft_base/memory.h>
#include "rt.h"
#include "image.h"
#include "ocl_data.h"

static size_t		ft_min(size_t arg1, size_t arg2)
{
	return (arg1 > arg2 ? arg2 : arg1);
}

//TODO CHANGE IT !!!!!!
static cl_int		compute_le_frame(t_rt *core, t_kargs *tmp,
		unsigned int *sample_seed)
{
	unsigned int	i;
	cl_int			ret;
	size_t			glob_dim[2];
	size_t			offset[2];

	glob_dim[1] = core->mem_info.wg_dim[1];
	printf("window dim: %ux%u\n", core->sdl.win_width, core->sdl.win_height);
	printf("frame dim: %ux%u\n", core->sdl.frame_width, core->sdl.frame_height);
	printf("wg dim: %zux%zu\n", core->mem_info.wg_dim[0], core->mem_info.wg_dim[1]);
	printf("wg nb: %zux%zu\n", core->mem_info.wg_nb[0], core->mem_info.wg_nb[1]);
	ft_bzero(offset, sizeof(size_t) * 3);
	i = 0;
	if (clSetKernelArg(core->ocl.kernel, 12, sizeof(unsigned int), sample_seed)
		!= CL_SUCCESS)
		return (!CL_SUCCESS);
	while (i < core->mem_info.wg_nb[1] * core->mem_info.wg_nb[0])
	{
		glob_dim[0] = core->mem_info.wg_dim[0] * ft_min((core->mem_info.wg_nb[0]
					- (i % core->mem_info.wg_nb[0])),
				core->mem_info.compute_units);
		offset[0] = core->mem_info.wg_dim[0] * (size_t)(i % core->mem_info.wg_nb[0]);
		offset[1] = glob_dim[1] * (size_t)(i / core->mem_info.wg_nb[0]);
		ret = clEnqueueNDRangeKernel(core->ocl.queue, core->ocl.kernel, 2,
				offset, glob_dim, core->mem_info.wg_dim, 0, NULL, NULL);
		if (ret != CL_SUCCESS && !release_kernel_arg(tmp))
			return (ret);
		i += glob_dim[0] / core->mem_info.wg_dim[0];
	}
	return (CL_SUCCESS);
}

cl_int				render_frame(t_rt *core, t_timer *t)
{
	t_kargs			*tmp;
	size_t			glob_dim[3];
	cl_int			ret;
	size_t			offset[3];
	unsigned int	sample_seed;

	sample_seed = ((core->sample_count == (core->sample_nb - 1)) ? 0 :
			(core->sample_count + 1)
			* (((unsigned int *)core->sample_sum)[42 * 4] + 1));
	if ((tmp = ocl_set_kernel_arg(core, &ret)) == NULL)
		return (ret);
	update_frame_size(core, &core->mem_info);
	if ((ret = compute_le_frame(core, tmp, &sample_seed)) != CL_SUCCESS)
		return (ret);
	ft_bzero(offset, sizeof(size_t) * 3);
	SDL_LockSurface(core->frame);
	glob_dim[0] = core->sdl.frame_width;
	glob_dim[1] = core->sdl.frame_height;
	glob_dim[2] = 1;
	ret = clEnqueueReadImage(core->ocl.queue, core->ocl.ocl_img, CL_TRUE,
			offset, glob_dim, 0, 0, core->frame->pixels, 0, NULL, NULL);
	if (ret != CL_SUCCESS)
	{
		printf("ret = %d\n", ret);
		return (ret);
	}
	average_sample(core);
	return (print_frame(core, t) + (int)release_kernel_arg(tmp) * 0);
}
