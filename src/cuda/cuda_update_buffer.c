/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_update_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:26:48 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 15:29:28 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cuda.h"
#include <cuda.h>
#include <cuda_runtime.h>

bool		cuda_update_buffer(t_cuda *cuda, size_t size, size_t target)
{
	if ((cuda->err = cudaFree(cuda->mem[target])) != cudaSuccess)
		return (cuda_error(cuda->err));
	if ((cuda->err = cudaMalloc(&(cuda->mem[target]), size) != cudaSuccess))
		return (cuda_error(cuda->err));
	return (true);
}
