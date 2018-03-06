/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:50:02 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/05 22:43:01 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

/*

int			opencl_build(t_env *e, unsigned int count)
{
	if ((e->err = clBuildProgram(e->program, 0, NULL, "-I ./kernel/includes/ ", \
				NULL, NULL)) != CL_SUCCESS)
		return (opencl_builderrors(e, 5, e->err));
	if (!(KRT = clCreateKernel(e->program, "ray_trace", &e->err)) \
		|| e->err != CL_SUCCESS)
		return (opencl_builderrors(e, 6, e->err));
	if (!(e->frame_buffer = clCreateBuffer(e->context, CL_MEM_WRITE_ONLY, \
		count, NULL, NULL)))
		return (opencl_builderrors(e, 7, e->err));
	if (!(e->target_obj_buf = clCreateBuffer(e->context, CL_MEM_WRITE_ONLY, \
		sizeof(t_hit), NULL, NULL)))
		return (opencl_builderrors(e, 7, e->err));
	opencl_allocate_scene_memory(e);
	return (0);
}

void		load_kernel(t_env *e)
{
	int		fd;
	int		ret;
	char	*line;

	if ((e->kernel_src = ft_strdup("#define FROM_KERNEL\n")) == NULL)
	{
		s_error("Error during allocating memory for kernel source code", e);
		exit(1);
	}
	if ((fd = open("./kernel/kernel.cl", O_RDONLY)) < 0)
		s_error("Error opening kernel", e);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		e->kernel_src = ft_strjoin_frs1(e->kernel_src, "\n");
		e->kernel_src = ft_strjoin_free(e->kernel_src, line);
	}
	(ret == -1 ? s_error("GNL read error", e) : 0);
	e->kernel_src = ft_strjoin_frs1(e->kernel_src, "\n");
	close(fd);
}

int			opencl_init(t_env *e, unsigned int count)
{
	load_kernel(e);
	if ((e->err = clGetDeviceIDs(NULL, e->gpu ? CL_DEVICE_TYPE_GPU : \
				CL_DEVICE_TYPE_CPU, 1, &e->device_id, NULL)) != CL_SUCCESS)
		return (opencl_builderrors(e, 1, e->err));
	if (!(e->context = clCreateContext(0, 1, &e->device_id, \
				NULL, NULL, &e->err)))
		return (opencl_builderrors(e, 2, e->err));
	if (!(e->queue = clCreateCommandQueue(e->context, \
				e->device_id, 0, &e->err)))
		return (opencl_builderrors(e, 3, e->err));
	if (!(e->program = clCreateProgramWithSource(e->context, 1, \
				(const char **)&e->kernel_src, NULL, &e->err)))
		return (opencl_builderrors(e, 4, e->err));
	opencl_build(e, count);
	return (0);
}
*/
