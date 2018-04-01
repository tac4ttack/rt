/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_construct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:57:19 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 17:39:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"

static bool			cl_builderrors(t_cl *cl, int err, int errorcode)
{
	size_t			len;
	char			buffer[50000];

	cl_print_error(errorcode);
	if (err == 1)
		ft_putendl("\nError: Failed to create platform/device group!");
	else if (err == 2)
		ft_putendl("\nError: Failed to create compute context!");
	else if (err == 3)
		ft_putendl("\nError: Failed to create commands queue!");
	else if (err == 4)
		ft_putendl("\nError: Failed to create compute program!");
	else if (err == 5)
	{
		ft_putendl("\nError: Failed to build program executable!\n");
		clGetProgramBuildInfo(cl->program, cl->device_id, \
				CL_PROGRAM_BUILD_LOG, sizeof(buffer), buffer, &len);
		ft_putendl(buffer);
	}
	else if (err == 6)
		ft_putendl("\nError: Failed to create compute kernel!\n");
	else if (err == 7)
		ft_putendl("\nError: Failed to allocate device memory!\n");
	return (false);
}

static bool			cl_load_src(t_cl *cl, const char *path)
{
	int				fd;

	fd = open(path, O_RDONLY);
	if (!fd)
	{
		ft_putstr_fd("Failed to load source.\n", 2);
		return (false);
	}
	read(fd, cl->kernel_src, MAX_SOURCE_SIZE);
	cl->src_size = ft_strlen(cl->kernel_src);
	close(fd);
	return (true);
}

static bool			cl_create_base(t_cl *cl, int type)
{
	if ((cl->err = clGetPlatformIDs(1, &cl->platform_id, &cl->num_platforms)) \
																!= CL_SUCCESS)
		return (cl_builderrors(cl, 1, cl->err));
	if ((cl->err = clGetDeviceIDs(NULL, type, 1, &cl->device_id, NULL)) \
																!= CL_SUCCESS)
		return (cl_builderrors(cl, 1, cl->err));
	if (!(cl->context = clCreateContext(0, 1, \
			(const cl_device_id *)&cl->device_id, NULL, NULL, &cl->err)))
		return (cl_builderrors(cl, 2, cl->err));
	if (!(cl->queue = clCreateCommandQueue(cl->context, cl->device_id, \
															0, &cl->err)))
		return (cl_builderrors(cl, 3, cl->err));
	if (!(cl->program = clCreateProgramWithSource(cl->context, 1, \
							(const char **)&cl->kernel_src, NULL, &cl->err)))
		return (cl_builderrors(cl, 4, cl->err));
	(void)type;
	return (true);
}

static bool			cl_build(t_cl *cl)
{
	if ((cl->err = clBuildProgram(cl->program, 0, NULL, \
					"-I ./kernel/includes/ ", NULL, NULL)) != CL_SUCCESS)
		return (cl_builderrors(cl, 5, cl->err));
	if (!(cl->kernel = clCreateKernel(cl->program, "ray_trace", &cl->err)) \
										|| cl->err != CL_SUCCESS)
		return (cl_builderrors(cl, 6, cl->err));
	if ((cl->err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
						CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t),
									&cl->local_item_size, NULL)))
		return (cl_builderrors(cl, 0, cl->err));
	return (true);
}

t_cl				*cl_construct(const char *path, \
					const size_t width, const size_t height, int type)
{
	t_cl			*cl;
	cl_ulong		size;

	if (!(cl = ft_memalloc(sizeof(t_cl))))
		return (NULL);
	if (!(cl->kernel_src = (char *)ft_memalloc(MAX_SOURCE_SIZE)))
		return (cl_destruct(&cl));
	if (!cl_load_src(cl, path) ||
		!cl_create_base(cl, type) ||
		!cl_build(cl))
		return (NULL);
	cl->add_buffer = &cl_add_buffer;
	cl->compute = &cl_compute;
	cl->dimension[0] = width;
	cl->dimension[1] = height;
	clGetDeviceInfo(cl->device_id, CL_DEVICE_LOCAL_MEM_SIZE, \
					sizeof(cl_ulong), &size, 0);
	return (cl);
}
