/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destruct_cl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:53:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/03/06 21:57:29 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		*destruct_cl(t_cl **ptr_cl)
{
	t_cl *cl;

	if (!ptr_cl || !(*ptr_cl))
		return (NULL);
	cl = *ptr_cl;
	if (cl->kernel)
		cl->err = clReleaseKernel(cl->kernel);
	cl_check_err(cl->err, "clReleaseKernel");
	if (cl->program)
		cl->err = clReleaseProgram(cl->program);
	cl_check_err(cl->err, "clReleaseProgram");
	while (cl->nb_mem)
	{
		if (cl->mem[cl->nb_mem - 1])
			cl->err = clReleaseMemObject(cl->mem[cl->nb_mem - 1]);
		cl->nb_mem--;
	}
	cl_check_err(cl->err, "clReleaseMemObject");
	if (cl->queue)
		cl->err = clReleaseCommandQueue(cl->queue);
	cl_check_err(cl->err, "clReleaseCommandQueue");
	if (cl->context)
		cl->err = clReleaseContext(cl->context);
	cl_check_err(cl->err, "clReleaseContext");
	if (cl->kernel_src)
		ft_memdel((void**)&cl->kernel_src);
	ft_memdel((void **)ptr_cl);
	return (NULL);
}
