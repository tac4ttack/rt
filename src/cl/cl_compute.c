/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_compute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:55:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/11 19:13:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"

bool		cl_compute(t_cl *cl)
{
	size_t global;
	size_t local;
	size_t *ptr_local;

	cl->event = 0;
	ptr_local = NULL;
	global = cl->dimension[0] * cl->dimension[1];
	if (cl->device_type == CL_DEVICE_TYPE_GPU && \
		(cl->dimension[0] * cl->dimension[1]) % 128 == 0)
	{
		local = 128;
		ptr_local = &local;
	}
	clFinish(cl->queue);
	if ((cl->err = clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL,
										&global,
										ptr_local,
										0, NULL, &cl->event)) != CL_SUCCESS)
		return (cl_print_error(cl->err));
	clWaitForEvents(1, &cl->event);
	cl->err |= clFlush(cl->queue);
	clReleaseEvent(cl->event);
	if (cl->err)
		return (cl_print_error(cl->err));
	return (true);
}
