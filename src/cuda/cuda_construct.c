/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cuda_construct.cu                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 15:26:34 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/20 18:14:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "t_cuda.h"
#include <cuda.h>

t_cuda		*cuda_construct(void)
{
	t_cuda *cuda;

	if (!(cuda = (t_cuda *)ft_memalloc(sizeof(t_cuda))))
		return (NULL);
	cuda->add_buffer = cuda_add_buffer;
	cuda->update_buffer = cuda_update_buffer;
	return (cuda);
}
