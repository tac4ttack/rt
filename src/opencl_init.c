/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:50:02 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/27 16:18:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			opencl_builderrors(t_env *e, int err, int errorcode)
{
	size_t	len;
	char	buffer[50000];

	opencl_print_error(errorcode);
	if (err == 1)
		ft_putendl("Error: Failed to create device group!");
	else if (err == 2)
		ft_putendl("Error: Failed to create compute context!");
	else if (err == 3)
		ft_putendl("Error: Failed to create commands queue!");
	else if (err == 4)
		ft_putendl("Error: Failed to create compute program!");
	else if (err == 5)
	{
		ft_putendl("Error: Failed to build program executable!\n");
		clGetProgramBuildInfo(e->program, e->device_id, \
				CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		ft_putendl(buffer);
	}
	else if (err == 6)
		ft_putendl("Error: Failed to create compute kernel!\n");
	else if (err == 7)
		ft_putendl("Error: Failed to allocate device memory!\n");
	if (err >= 5)
		exit(1);
	return (EXIT_FAILURE);
}

int			opencl_build(t_env *e, unsigned int count)
{
	if ((e->err = clBuildProgram(e->program, 0, NULL, "-g -I ./kernel/includes/ ", \
				NULL, NULL)) != CL_SUCCESS)
		return (opencl_builderrors(e, 5, e->err));
	if (!(KRT = clCreateKernel(e->program, "ray_trace", &e->err)) \
		|| e->err != CL_SUCCESS)
		return (opencl_builderrors(e, 6, e->err));
	if (!(e->kernel_sepia = clCreateKernel(e->program, "sepia_shader", &e->err)) \
		|| e->err != CL_SUCCESS)
		return (opencl_builderrors(e, 6, e->err));
	if (!(e->kernel_bw = clCreateKernel(e->program, "bw_shader", &e->err)) \
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
	if (!(e->raytrace_queue = clCreateCommandQueue(e->context, \
				e->device_id, 0, &e->err)))
		return (opencl_builderrors(e, 3, e->err));
	if (!(e->program = clCreateProgramWithSource(e->context, 1, \
				(const char **)&e->kernel_src, NULL, &e->err)))
		return (opencl_builderrors(e, 4, e->err));
	opencl_build(e, count);
	return (0);
}
