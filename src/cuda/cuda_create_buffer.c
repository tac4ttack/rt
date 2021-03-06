/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_create_buffer.cu                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:26:53 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/20 19:00:50 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cuda.h"
#include <cuda.h>
#include <cuda_runtime.h>

bool		cuda_add_buffer(t_cuda *cuda, size_t size)
{
	if (!(cuda->mem = (void **)ft_memrealloc(cuda->mem,
					sizeof(void **) * cuda->nb_mem,
					sizeof(void **) * (cuda->nb_mem + 1))))
		return (false);
	if ((cuda->err = cudaMalloc(&(cuda->mem[cuda->nb_mem]), size))
														!= cudaSuccess)
		return (cuda_error(cuda->err));
	cuda->nb_mem++;
	return (true);
}
