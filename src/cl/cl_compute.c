/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_compute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:55:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/07 22:48:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"

bool		cl_compute(t_cl *cl)
{
	cl->event = 0;
	cl->err = clEnqueueNDRangeKernel(cl->queue, cl->kernel, 2, NULL,
										cl->dimension,
										NULL,
										0, NULL, &cl->event);
	clFinish(cl->queue);
	if (cl->err)
		return (cl_print_error(cl->err));
	return (true);
}
