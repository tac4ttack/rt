/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:08:30 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/03/02 23:41:55 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cl_load_src(t_cl *cl, const char *path, char *k_src,
													size_t *src_size)
{
	int		fd;

	(void)cl;
	*src_size = 0;
	fd = open(path, O_RDONLY);
	if (!fd)
	{
		ft_putstr_fd("Failed to load source.\n", 2);
		exit(0);
	}
	read(fd, k_src, MAX_SOURCE_SIZE);
	*src_size = ft_strlen(k_src);
	close(fd);
}

static void		cl_create_base(t_cl *cl, const char *path)
{
	char	*k_src;
	size_t	src_size;

	k_src = (char *)ft_memalloc(MAX_SOURCE_SIZE);
	cl->err = clGetPlatformIDs(1, &(cl->platform_id), &(cl->ret_num_platforms));
	cl_check_err(cl->err, "clGetPlatformIDs");
	cl->err = clGetDeviceIDs(cl->platform_id, CL_DEVICE_TYPE_GPU,
			1, &(cl->device_id), &(cl->ret_num_devices));
	cl_check_err(cl->err, "clGetDeviceIDs");
	cl->context = clCreateContext(NULL, 1,
								&(cl->device_id), NULL, NULL, &(cl->err));
	cl_check_err(cl->err, "clCreateContext");
	cl->cq = clCreateCommandQueue(cl->context,
								cl->device_id, 0, &(cl->err));
	cl_check_err(cl->err, "clCreateCommandQueue");
	cl_load_src(cl, path, k_src, &src_size);
	cl->program = clCreateProgramWithSource(cl->context,
										1, (const char **)&k_src,
			NULL, &(cl->err));
	cl_check_err(cl->err, "clCreateProgramWithSource");
	ft_strdel(&k_src);
}

static void		cl_compile_kernel(t_cl *cl)
{
	char		buffer[CL_ERROR_LEN_BUFFER];
	size_t		len;

	cl->err = clBuildProgram(cl->program, 0, NULL,
								"-I ./kernel/includes/ ", NULL, NULL);
	if (cl->err != CL_SUCCESS)
	{
		ft_bzero(buffer, CL_ERROR_LEN_BUFFER);
		cl->err = clGetProgramBuildInfo(cl->program, cl->device_id,
				CL_PROGRAM_BUILD_LOG, CL_ERROR_LEN_BUFFER, buffer, &len);
		if (cl->err == CL_SUCCESS)
			printf("\033[31mCompiler error :%zu\033[0m\n%s", len, buffer);
		else
			cl_check_err(cl->err, "Erreur étonnante : clGetProgramBuildInfo");
		exit(EXIT_FAILURE);
	}
}

int				cl_init(t_cl *cl, const char *path, const char *name,
												const size_t global_item_size)
{
	cl_create_base(cl, path);
	cl_compile_kernel(cl);
	cl->kernel = clCreateKernel(cl->program, name, &(cl->err));
	cl_check_err(cl->err, "clCreateKernel");
	cl->global_item_size = global_item_size;
	cl->err = clGetKernelWorkGroupInfo(cl->kernel, cl->device_id,
						CL_KERNEL_WORK_GROUP_SIZE, sizeof(size_t),
									&cl->local_item_size, NULL);
	if (cl->global_item_size % cl->local_item_size)
	{
		dprintf(2, "Global_item_size %% Local item size != 0 \
				\n(%zu) %% (%zu) = %zu\n",
				cl->global_item_size, cl->local_item_size,
				cl->global_item_size % cl->local_item_size);
		exit(EXIT_FAILURE);
	}
	cl_check_err(cl->err, "clGetKernelWorkGroup");
	return (1);
}
