/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:40:38 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/05 22:16:56 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cl_write_buffer(t_env *e, t_cl *cl)
{
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[1], CL_TRUE, 0,
							e->gen_objects->mem_size,
							e->gen_objects->mem, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[2], CL_TRUE, 0,
							sizeof(t_scene),
							e->scene, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[3], CL_TRUE, 0,
							sizeof(t_cam) * NCAM,
							e->cameras, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[4], CL_TRUE, 0,
							e->gen_lights->mem_size,
							e->gen_lights->mem, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
}


void		opencl_set_args(t_env *e)
{
	cl_write_buffer(e, &e->cl);
	e->cl.err = 0;
	e->cl.err = clSetKernelArg(KRT, 0, sizeof(cl_mem), &e->cl.mem[0]);
	e->cl.err |= clSetKernelArg(KRT, 1, sizeof(cl_mem), &e->cl.mem[1]);
	e->cl.err |= clSetKernelArg(KRT, 2, e->gen_objects->mem_size, NULL);
	e->cl.err |= clSetKernelArg(KRT, 3, sizeof(size_t), &e->gen_objects->mem_size);

	e->cl.err |= clSetKernelArg(KRT, 4, sizeof(float), &(e->fps.u_time));

	e->cl.err |= clSetKernelArg(KRT, 5, sizeof(cl_mem), &e->cl.mem[2]);
	e->cl.err |= clSetKernelArg(KRT, 6, sizeof(cl_mem), &e->cl.mem[3]);

	e->cl.err |= clSetKernelArg(KRT, 7, sizeof(t_scene), NULL);
	e->cl.err |= clSetKernelArg(KRT, 8, sizeof(t_cam) * NCAM, NULL);

	e->cl.err |= clSetKernelArg(KRT, 9, sizeof(cl_mem), &e->cl.mem[4]);
	e->cl.err |= clSetKernelArg(KRT, 10, e->gen_lights->mem_size, NULL);
	e->cl.err |= clSetKernelArg(KRT, 11, sizeof(size_t), &e->gen_lights->mem_size);

	e->cl.err |= clSetKernelArg(KRT, 12, sizeof(cl_mem), &e->cl.mem[5]);


	if (e->cl.err != CL_SUCCESS)
		s_error("Error: Failed to send arguments to kernel!", e);
}

int			draw(t_env *e)
{
	t_cl *cl = &e->cl;

	opencl_set_args(e);
	cl_event event;
	event = 0;
	cl->err = clEnqueueNDRangeKernel(cl->cq, cl->kernel, 1, NULL,
										&cl->global_item_size,
										&cl->local_item_size,
										0, NULL, &event);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
	clWaitForEvents(1, &event);
	cl_check_err(cl->err, "clEnqueueNDRangeKernel");
	cl->err = clFlush(cl->cq);
	cl_check_err(cl->err, "clFlush");
	clReleaseEvent(event);

	cl->err = clEnqueueReadBuffer(cl->cq, cl->mem[0], CL_TRUE, 0,
			e->scene->win_w * e->scene->win_h * 4,
			e->frame->pix, 0, NULL, NULL);
	if (e->scene->flag & OPTION_RUN)
	{
		cl->err = clEnqueueReadBuffer(cl->cq, cl->mem[5], CL_FALSE, 0,
			sizeof(int),
			&e->target, 0, NULL, NULL);
		e->scene->flag ^= OPTION_RUN;
	}
	return (0);
}

void		opencl_close(t_env *e)
{
	clReleaseMemObject(e->cl.mem[0]);
	clReleaseMemObject(e->cl.mem[1]);
	clReleaseMemObject(e->cl.mem[2]);
	clReleaseMemObject(e->cl.mem[3]);
	clReleaseMemObject(e->cl.mem[4]);
	clReleaseMemObject(e->cl.mem[5]);
	clReleaseProgram(e->cl.program);
	clReleaseKernel(e->cl.kernel);
	clReleaseCommandQueue(e->cl.cq);
	clReleaseContext(e->cl.context);
}
