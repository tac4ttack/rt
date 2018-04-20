/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_destruct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:27:01 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/20 18:57:49 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cuda.h"
#include <cuda.h>
#include <cuda_runtime.h>

void		*cuda_destruct(t_cuda **ptr_cuda)
{
	t_cuda *cuda;

	if (!ptr_cuda || !(*ptr_cuda))
		return (NULL);
	cuda = *ptr_cuda;
	while (cuda->nb_mem)
	{
		if (cuda->mem[cuda->nb_mem - 1])
		{
			if ((cuda->err = cudaFree(cuda->mem[cuda->nb_mem - 1]))
														!= cudaSuccess)
				return (cuda_ptr_error(cuda->err));
		}
		cuda->nb_mem--;
	}
	ft_memdel((void **)&cuda->mem);
	ft_memdel((void **)ptr_cuda);
	return (NULL);
}
