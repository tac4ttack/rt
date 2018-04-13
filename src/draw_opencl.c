/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/13 17:32:43 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/13 18:39:49 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

#	ifdef DCL

static void		cl_write_buffer(t_env *e, t_cl *cl)
{
	if ((cl->err = clEnqueueWriteBuffer(cl->queue, cl->mem[1], CL_TRUE, 0,
							e->gen_objects->mem_size,
							e->gen_objects->mem, 0, NULL, NULL)))
		s_error("Error: Failed to send arguments to kernel!", e);
	if ((cl->err = clEnqueueWriteBuffer(cl->queue, cl->mem[2], CL_TRUE, 0,
							sizeof(t_scene),
							e->scene, 0, NULL, NULL)))
		s_error("Error: Failed to send arguments to kernel!", e);
	if ((cl->err = clEnqueueWriteBuffer(cl->queue, cl->mem[3], CL_TRUE, 0,
							sizeof(t_cam) * NCAM,
							e->cameras, 0, NULL, NULL)))
		s_error("Error: Failed to send CAM arguments to kernel!", e);
	if ((cl->err = clEnqueueWriteBuffer(cl->queue, cl->mem[4], CL_TRUE, 0,
							e->gen_lights->mem_size,
							e->gen_lights->mem, 0, NULL, NULL)))
		s_error("Error: Failed to send arguments to kernel!", e);
}

void			opencl_set_args(t_env *e, t_cl *cl)
{
	cl_write_buffer(e, cl);
	cl->err = 0;
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->mem[0]);
	cl->err |= clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->mem[1]);
	cl->err |= clSetKernelArg(cl->kernel, 2, e->gen_objects->mem_size, NULL);
	cl->err |= clSetKernelArg(cl->kernel, 3, 4, &e->gen_objects->mem_size);
	cl->err |= clSetKernelArg(cl->kernel, 4, sizeof(float), &(e->fps.u_time));
	cl->err |= clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), &cl->mem[2]);
	cl->err |= clSetKernelArg(cl->kernel, 6, sizeof(cl_mem), &cl->mem[3]);
	cl->err |= clSetKernelArg(cl->kernel, 7, sizeof(t_scene), NULL);
	cl->err |= clSetKernelArg(cl->kernel, 8, sizeof(t_cam) * NCAM, NULL);
	cl->err |= clSetKernelArg(cl->kernel, 9, sizeof(cl_mem), &cl->mem[4]);
	cl->err |= clSetKernelArg(cl->kernel, 10, e->gen_lights->mem_size, NULL);
	cl->err |= clSetKernelArg(cl->kernel, 11, 4, &e->gen_lights->mem_size);
	cl->err |= clSetKernelArg(cl->kernel, 12, sizeof(cl_mem), &cl->mem[5]);
	cl->err |= clSetKernelArg(cl->kernel, 13, sizeof(cl_mem), &cl->mem[6]);
	cl->err |= clSetKernelArg(cl->kernel, 14, sizeof(cl_mem), &cl->mem[7]);
	cl->err |= clSetKernelArg(cl->kernel, 15, sizeof(cl_mem), &cl->mem[8]);
	cl->err |= clSetKernelArg(cl->kernel, 16, sizeof(cl_mem), &cl->mem[9]);
	if (cl->err != CL_SUCCESS)
		s_error("Error: Failed to send arguments to kernel!", e);
}

int				draw(t_env *e)
{
	t_cl		*cl;

	cl = e->cl;
	opencl_set_args(e, cl);
	cl->compute(cl);
	cl->err = clEnqueueReadBuffer(cl->queue, cl->mem[0], CL_TRUE, 0,
									e->scene->win_w * e->scene->win_h * 4,
									e->pixel_data, 0, NULL, NULL);
	if (e->scene->flag & OPTION_RUN)
	{
		cl->err = clEnqueueReadBuffer(cl->queue, cl->mem[5], CL_TRUE, 0,
			sizeof(int),
			&e->target, 0, NULL, NULL);
		e->scene->flag ^= OPTION_RUN;
	}
	return (0);
}
#	endif
