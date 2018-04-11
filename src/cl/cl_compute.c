/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_compute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:55:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/11 15:13:42 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cl.h"

bool		cl_compute(t_cl *cl)
{	
	cl->event = 0;
	
	// DEBUG, ajout pour voir si ça supprime l'abort sauvage
	// 09/04/2018 13:50:30 putain je viens de foutre le truc et j'abort direct....
	clFinish(cl->queue);

	// Fixed worksize
	// cl->err = clEnqueueNDRangeKernel(cl->queue, cl->kernel, 2, NULL,
	// 									cl->dimension,
	// 									NULL,
	// 									0, NULL, &cl->event);
	
	// Custom worksize
	size_t global = cl->dimension[0] * cl->dimension[1];
	size_t local = 128;
	cl->err = clEnqueueNDRangeKernel(cl->queue, cl->kernel, 1, NULL,
										&global,
										&local,
										0, NULL, &cl->event);
										
	clWaitForEvents(1, &cl->event);
	cl->err |= clFlush(cl->queue);
	clReleaseEvent(cl->event);
	if (cl->err)
		return (cl_print_error(cl->err));
	return (true);
}
