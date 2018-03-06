/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:40:38 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/06 20:22:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		cl_write_buffer(t_env *e, t_cl *cl)
{
	cl->err = clEnqueueWriteBuffer(cl->queue, cl->mem[1], CL_TRUE, 0,
							e->gen_objects->mem_size,
							e->gen_objects->mem, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clEnqueueWriteBuffer(cl->queue, cl->mem[2], CL_TRUE, 0,
							sizeof(t_scene),
							e->scene, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clEnqueueWriteBuffer(cl->queue, cl->mem[3], CL_TRUE, 0,
							sizeof(t_cam) * NCAM,
							e->cameras, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
	cl->err = clEnqueueWriteBuffer(cl->queue, cl->mem[4], CL_TRUE, 0,
							e->gen_lights->mem_size,
							e->gen_lights->mem, 0, NULL, NULL);
	cl_check_err(cl->err, "clEnqueueWriteBuffer mem_obj");
}


void		opencl_set_args(t_env *e, t_cl *cl)
{
	cl_write_buffer(e, cl);
	cl->err = 0;
	cl->err = clSetKernelArg(cl->kernel, 0, sizeof(cl_mem), &cl->mem[0]);
	cl->err |= clSetKernelArg(cl->kernel, 1, sizeof(cl_mem), &cl->mem[1]);
	cl->err |= clSetKernelArg(cl->kernel, 2, e->gen_objects->mem_size, NULL);
	cl->err |= clSetKernelArg(cl->kernel, 3, sizeof(size_t), &e->gen_objects->mem_size);

	cl->err |= clSetKernelArg(cl->kernel, 4, sizeof(float), &(e->fps.u_time));

	cl->err |= clSetKernelArg(cl->kernel, 5, sizeof(cl_mem), &cl->mem[2]);
	cl->err |= clSetKernelArg(cl->kernel, 6, sizeof(cl_mem), &cl->mem[3]);

	cl->err |= clSetKernelArg(cl->kernel, 7, sizeof(t_scene), NULL);
	cl->err |= clSetKernelArg(cl->kernel, 8, sizeof(t_cam) * NCAM, NULL);

	cl->err |= clSetKernelArg(cl->kernel, 9, sizeof(cl_mem), &cl->mem[4]);
	cl->err |= clSetKernelArg(cl->kernel, 10, e->gen_lights->mem_size, NULL);
	cl->err |= clSetKernelArg(cl->kernel, 11, sizeof(size_t), &e->gen_lights->mem_size);

	cl->err |= clSetKernelArg(cl->kernel, 12, sizeof(cl_mem), &cl->mem[5]);


	if (cl->err != CL_SUCCESS)
		s_error("Error: Failed to send arguments to kernel!", e);
}

int			draw(t_env *e)
{
	t_cl *cl = e->cl;
	//const size_t g[2] = {e->scene->win_w, e->scene->win_h};

	opencl_set_args(e, cl);

	cl->compute(cl);

	cl->err = clEnqueueReadBuffer(cl->queue, cl->mem[0], CL_TRUE, 0,
			e->scene->win_w * e->scene->win_h * 4,
			e->frame->pix, 0, NULL, NULL);
	if (e->scene->flag & OPTION_RUN)
	{
		cl->err = clEnqueueReadBuffer(cl->queue, cl->mem[5], CL_FALSE, 0,
			sizeof(int),
			&e->target, 0, NULL, NULL);
		e->scene->flag ^= OPTION_RUN;
	}
	return (0);
}
