/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_destruct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 17:53:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/03/07 20:25:08 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"

void		*cl_destruct(t_cl **ptr_cl)
{
	t_cl *cl;

	if (!ptr_cl || !(*ptr_cl))
		return (NULL);
	cl = *ptr_cl;
	if (cl->kernel)
		cl->err = clReleaseKernel(cl->kernel);
	if (cl->program)
		cl->err = clReleaseProgram(cl->program);
	while (cl->nb_mem)
	{
		if (cl->mem[cl->nb_mem - 1])
			cl->err = clReleaseMemObject(cl->mem[cl->nb_mem - 1]);
		cl->nb_mem--;
	}
	if (cl->queue)
		cl->err = clReleaseCommandQueue(cl->queue);
	if (cl->context)
		cl->err = clReleaseContext(cl->context);
	if (cl->kernel_src)
		ft_memdel((void**)&cl->kernel_src);
	ft_memdel((void **)ptr_cl);
	return (NULL);
}
