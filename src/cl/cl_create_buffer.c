/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_create_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:59:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/08 01:32:30 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"

bool		cl_replace_buffer(t_cl *cl, size_t size, size_t target)
{
	if (clReleaseMemObject(cl->mem[target]) == CL_INVALID_MEM_OBJECT)
		ft_putendl("error in replace buffer");
	cl->mem[target] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			size, NULL, &(cl->err));
	if (cl->err)
		return (false);
	return (true);
}

bool		cl_add_buffer(t_cl *cl, size_t size)
{
	if (!(cl->mem = ft_memrealloc(cl->mem,
					sizeof(cl_mem) * cl->nb_mem,
					sizeof(cl_mem) * (cl->nb_mem + 1))))
		return (false);
	cl->mem[cl->nb_mem] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			size, NULL, &(cl->err));
	if (cl->err)
		return (false);
	cl->nb_mem++;
	return (true);
}
