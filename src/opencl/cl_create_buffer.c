/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_create_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:59:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/03/02 23:28:25 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

bool		cl_create_buffer(t_cl *cl, size_t size)
{
	if (!(cl->mem = ft_memrealloc(cl->mem,
					sizeof(cl_mem) * cl->nb_mem,
					sizeof(cl_mem) * (cl->nb_mem + 1))))
		return (false);
	cl->mem[cl->nb_mem] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			size, NULL, &(cl->err));
	cl_check_err(cl->err, "clCreateBuffer");
	cl->nb_mem++;
	return (true);
}
