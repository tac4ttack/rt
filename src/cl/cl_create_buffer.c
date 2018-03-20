/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_create_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:59:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/03/20 17:25:45 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"

bool		cl_replace_buffer(t_cl *cl, size_t size, size_t target)
{
	ft_putendl("im in replace buffer");
//	if (!(cl->mem = ft_memrealloc(cl->mem,
//					sizeof(cl_mem) * cl->nb_mem,
//					sizeof(cl_mem) * (cl->nb_mem + 1))))
//		return (false);
//	clReleaseMemObject(cl->mem[target]);
	cl->mem[target] = clCreateBuffer(cl->context, CL_MEM_READ_WRITE,
			size, NULL, &(cl->err));
	if (cl->err)
		return (false);
	return (true);
}




bool		cl_add_buffer(t_cl *cl, size_t size)
{
	ft_putendl("im in add buffer");
	printf("nb meme = %zu\n", cl->nb_mem);
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
