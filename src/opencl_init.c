/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 18:50:02 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/06 19:08:51 by fmessina         ###   ########.fr       */
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
		ft_putendl("\nError: Failed to build program executable!\n");
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

int			opencl_build(t_env *e)
{
	if ((e->err = clBuildProgram(e->program, 0, NULL, "-I ./kernel/includes/ ", \
				NULL, NULL)) != CL_SUCCESS)
		return (opencl_builderrors(e, 5, e->err));
	ft_putendl("\x1b[1;32mOpenCL program built!\x1b[0m");
	if (!(KRT = clCreateKernel(e->program, "ray_trace", &e->err)) \
		|| e->err != CL_SUCCESS)
		return (opencl_builderrors(e, 6, e->err));
	ft_putendl("\x1b[1;32mOpenCL RAYTRACE kernel built!\n\x1b[0m");
	if (!(e->frame_buffer = clCreateBuffer(e->context, CL_MEM_WRITE_ONLY, \
		e->count * sizeof(int), NULL, NULL)))
		return (opencl_builderrors(e, 7, e->err));
	ft_putendl("\x1b[1;32mOpenCL frame buffer allocated!\x1b[0m");
	if (!(e->target_obj_buf = clCreateBuffer(e->context, CL_MEM_WRITE_ONLY, \
		sizeof(t_hit), NULL, NULL)))
		return (opencl_builderrors(e, 7, e->err));
	ft_putendl("\x1b[1;32mOpenCL target object buffer allocated!\n\x1b[0m");
	opencl_allocate_scene_memory(e);
	return (0);
}

void		load_kernel(t_env *e)
{
	int		fd;
	int		ret;
	char	*line;

	ft_putendl("\x1b[1;32mReading OpenCL kernel sources...\x1b[0m");
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
	ft_putendl("\x1b[1;32mOpenCL kernel sources successfully read!\n\x1b[0m");
}

int			opencl_init(t_env *e)
{
	ft_putendl("\n\x1b[1;32m/\\ Initializing OpenCL /\\\x1b[0m\n");
	load_kernel(e);
	if ((e->err = clGetDeviceIDs(NULL, e->gpu ? CL_DEVICE_TYPE_GPU : \
				CL_DEVICE_TYPE_CPU, 1, &e->device_id, NULL)) != CL_SUCCESS)
		return (opencl_builderrors(e, 1, e->err));
	ft_putendl("\x1b[1;32mOpenCL devices found!\x1b[0m");
	if (!(e->context = clCreateContext(0, 1, &e->device_id, \
				NULL, NULL, &e->err)))
		return (opencl_builderrors(e, 2, e->err));
	ft_putendl("\x1b[1;32mOpenCL context created!\x1b[0m");
	if (!(e->queue = clCreateCommandQueue(e->context, \
				e->device_id, 0, &e->err)))
		return (opencl_builderrors(e, 3, e->err));
	ft_putendl("\x1b[1;32mOpenCL command queue created!\x1b[0m");
	if (!(e->program = clCreateProgramWithSource(e->context, 1, \
				(const char **)&e->kernel_src, NULL, &e->err)))
		return (opencl_builderrors(e, 4, e->err));
	ft_putendl("\x1b[1;32mOpenCL program compiled!\x1b[0m");
	opencl_build(e);
	return (0);
}
