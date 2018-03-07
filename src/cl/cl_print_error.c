/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:31:43 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/07 18:48:10 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"

static void		opencl_print_error_part_four(const int err)
{
	(err == -59 ? ft_putstr("\x1b[1;31m\nCL_INVALID_OPERATION\x1b[0m") : 0);
	(err == -60 ? ft_putstr("\x1b[1;31m\nCL_INVALID_GL_OBJECT\x1b[0m") : 0);
	(err == -61 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_BUFFER_SIZE\x1b[0m") : 0);
	(err == -62 ? ft_putstr("\x1b[1;31m\nCL_INVALID_MIP_LEVEL\x1b[0m") : 0);
	(err == -63 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_GLOBAL_WORK_SIZE\x1b[0m") : 0);
	(err == -64 ? ft_putstr("\x1b[1;31m\nCL_INVALID_PROPERTY\x1b[0m") : 0);
	(err == -65 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_IMAGE_DESCRIPTOR\x1b[0m") : 0);
	(err == -66 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_COMPILER_OPTIONS\x1b[0m") : 0);
	(err == -67 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_LINKER_OPTIONS\x1b[0m") : 0);
	(err == -68 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_DEVICE_PARTITION_COUNT\x1b[0m") : 0);
}

static void		opencl_print_error_part_three(const int err)
{
	(err == -45 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_PROGRAM_EXECUTABLE\x1b[0m") : 0);
	(err == -46 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_KERNEL_NAME\x1b[0m") : 0);
	(err == -47 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_KERNEL_DEFINITION\x1b[0m") : 0);
	(err == -48 ? ft_putstr("\x1b[1;31m\nCL_INVALID_KERNEL\x1b[0m") : 0);
	(err == -49 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_ARG_INDEX\x1b[0m") : 0);
	(err == -50 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_ARG_VALUE\x1b[0m") : 0);
	(err == -51 ? ft_putstr("\x1b[1;31m\nCL_INVALID_ARG_SIZE\x1b[0m") : 0);
	(err == -52 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_KERNEL_ARGS\x1b[0m") : 0);
	(err == -53 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_WORK_DIMENSION\x1b[0m") : 0);
	(err == -54 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_WORK_GROUP_SIZE\x1b[0m") : 0);
	(err == -55 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_WORK_ITEM_SIZE\x1b[0m") : 0);
	(err == -56 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_GLOBAL_OFFSET\x1b[0m") : 0);
	(err == -57 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_EVENT_WAIT_LIST\x1b[0m") : 0);
	(err == -58 ? ft_putstr("\x1b[1;31m\nCL_INVALID_EVENT\x1b[0m") : 0);
}

static void		opencl_print_error_part_two(const int err)
{
	(err == -17 ? ft_putstr("\x1b[1;31m\nCL_LINK_PROGRAM_FAILURE\x1b[0m") : 0);
	(err == -18 ? ft_putstr(\
	"\x1b[1;31m\nCL_DEVICE_PARTITION_FAILED\x1b[0m") : 0);
	(err == -19 ? ft_putstr(\
	"\x1b[1;31m\nCL_KERNEL_ARG_INFO_NOT_AVAILABLE\x1b[0m") : 0);
	(err == -30 ? ft_putstr("\x1b[1;31m\nCL_INVALID_VALUE\x1b[0m") : 0);
	(err == -31 ? ft_putstr("\x1b[1;31m\nCL_INVALID_DEVICE_TYPE\x1b[0m") : 0);
	(err == -32 ? ft_putstr("\x1b[1;31m\nCL_INVALID_PLATFORM\x1b[0m") : 0);
	(err == -33 ? ft_putstr("\x1b[1;31m\nCL_INVALID_DEVICE\x1b[0m") : 0);
	(err == -34 ? ft_putstr("\x1b[1;31m\nCL_INVALID_CONTEXT\x1b[0m") : 0);
	(err == -35 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_QUEUE_PROPERTIES\x1b[0m") : 0);
	(err == -36 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_COMMAND_QUEUE\x1b[0m") : 0);
	(err == -37 ? ft_putstr("\x1b[1;31m\nCL_INVALID_HOST_PTR\x1b[0m") : 0);
	(err == -38 ? ft_putstr("\x1b[1;31m\nCL_INVALID_MEM_OBJECT\x1b[0m") : 0);
	(err == -39 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_IMAGE_FORMAT_DESCRIPTOR\x1b[0m") : 0);
	(err == -40 ? ft_putstr("\x1b[1;31m\nCL_INVALID_IMAGE_SIZE\x1b[0m") : 0);
	(err == -41 ? ft_putstr("\x1b[1;31m\nCL_INVALID_SAMPLER\x1b[0m") : 0);
	(err == -42 ? ft_putstr("\x1b[1;31m\nCL_INVALID_BINARY\x1b[0m") : 0);
	(err == -43 ? ft_putstr(\
	"\x1b[1;31m\nCL_INVALID_BUILD_OPTIONS\x1b[0m") : 0);
	(err == -44 ? ft_putstr("\x1b[1;31m\nCL_INVALID_PROGRAM\x1b[0m") : 0);
}

static void		opencl_print_error_part_one(const int err)
{
	(err == 0 ? ft_putstr("\x1b[1;31m\nCL_SUCCESS\x1b[0m") : 0);
	(err == -1 ? ft_putstr("\x1b[1;31m\nCL_DEVICE_NOT_FOUND\x1b[0m") : 0);
	(err == -2 ? ft_putstr("\x1b[1;31m\nCL_DEVICE_NOT_AVAILABLE\x1b[0m") : 0);
	(err == -3 ? ft_putstr(\
	"\x1b[1;31m\nCL_COMPILER_NOT_AVAILABLE\x1b[0m") : 0);
	(err == -4 ? ft_putstr(\
	"\x1b[1;31m\nCL_MEM_OBJECT_ALLOCATION_FAILURE\x1b[0m") : 0);
	(err == -5 ? ft_putstr("\x1b[1;31m\nCL_OUT_OF_RESOURCES\x1b[0m") : 0);
	(err == -6 ? ft_putstr("\x1b[1;31m\nCL_OUT_OF_HOST_MEMORY\x1b[0m") : 0);
	(err == -7 ? ft_putstr(\
	"\x1b[1;31m\nCL_PROFILING_INFO_NOT_AVAILABLE\x1b[0m") : 0);
	(err == -8 ? ft_putstr("\x1b[1;31m\nCL_MEM_COPY_OVERLAP\x1b[0m") : 0);
	(err == -9 ? ft_putstr("\x1b[1;31m\nCL_IMAGE_FORMAT_MISMATCH\x1b[0m") : 0);
	(err == -10 ? ft_putstr(\
	"\x1b[1;31m\nCL_IMAGE_FORMAT_NOT_SUPPORTED\x1b[0m") : 0);
	(err == -11 ? ft_putstr(\
	"\x1b[1;31m\nCL_BUILD_PROGRAM_FAILURE\x1b[0m") : 0);
	(err == -12 ? ft_putstr("\x1b[1;31m\nCL_MAP_FAILURE\x1b[0m") : 0);
	(err == -13 ? ft_putstr(" \
	\x1b[1;31m\nCL_MISALIGNED_SUB_BUFFER_OFFSET\x1b[0m") : 0);
	(err == -14 ? ft_putstr(\
	"\x1b[1;31m\nCL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST\x1b[0m") : 0);
	(err == -15 ? ft_putstr(\
	"\x1b[1;31m\nCL_COMPILE_PROGRAM_FAILURE\x1b[0m") : 0);
	(err == -16 ? ft_putstr("\x1b[1;31m\nCL_LINKER_NOT_AVAILABLE\x1b[0m") : 0);
}

bool			cl_print_error(int err)
{
	if (err <= -0 && err >= -16)
		opencl_print_error_part_one(err);
	else if ((err <= -17 && err >= -19) || (err <= -30 && err >= -44))
		opencl_print_error_part_two(err);
	else if ((err <= -45 && err >= -58))
		opencl_print_error_part_three(err);
	else if (err <= -59 && err >= -68)
		opencl_print_error_part_four(err);
	else if (err <= -1000 && err >= -1004)
	{
		(err == -1000 ? ft_putstr(\
		"\x1b[1;31m\nCL_INVALID_GL_SHAREGROUP_REFERENCE_KHR\x1b[0m") : 0);
		(err == -1001 ? ft_putstr(\
		"\x1b[1;31m\nCL_PLATFORM_NOT_FOUND_KHR\x1b[0m") : 0);
		(err == -1002 ? ft_putstr(\
		"\x1b[1;31m\nCL_INVALID_D3D10_DEVICE_KHR\x1b[0m") : 0);
		(err == -1003 ? ft_putstr(\
		"\x1b[1;31m\nCL_INVALID_D3D10_RESOURCE_KHR\x1b[0m") : 0);
		(err == -1004 ? ft_putstr(\
		"\x1b[1;31m\nCL_D3D10_RESOURCE_ALREADY_ACQUIRED_KHR\x1b[0m") : 0);
	}
	else
		ft_putstr("\x1b[2;31m\nUnknown OpenCL error\n");
	if (err)
		return (false);
	return (true);
}
