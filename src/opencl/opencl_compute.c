/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:40:38 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/04 21:23:23 by ntoniolo         ###   ########.fr       */
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
	/*printf("Light:\n%.2f %.2f %.2f\nColor %x\n",
						e->lights->pos.x,
						e->lights->pos.y,
						e->lights->pos.z,
						e->lights->color
					);*/
	cl->err = clEnqueueWriteBuffer(cl->cq, cl->mem[4], CL_TRUE, 0,
							sizeof(t_light) * NLIG,
							e->lights, 0, NULL, NULL);
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
	e->cl.err |= clSetKernelArg(KRT, 7, sizeof(cl_mem), &e->cl.mem[4]);

	e->cl.err |= clSetKernelArg(KRT, 8, sizeof(t_scene), NULL);
	e->cl.err |= clSetKernelArg(KRT, 9, sizeof(t_cam) * NCAM, NULL);
	e->cl.err |= clSetKernelArg(KRT, 10, sizeof(t_light) * NLIG, NULL);
	if (e->cl.err != CL_SUCCESS)
	{
		//opencl_print_error(e->cl.err);
		s_error("Error: Failed to send arguments to kernel!", e);
	}
}

/*
** the "CL_TRUE" flag blocks the read operation until
** 	all work items have finished their computation
*/
/*
int			get_imgptr(t_env *e)
{
	printf("Nb %zu\n", e->gen_objects->unit_size);
	clFinish(e->queue);
	e->cl.err = clEnqueueReadBuffer(e->queue, e->frame_buffer, CL_TRUE, 0, \
			(e->count * 4), e->frame->pix, 0, NULL, &e->events[3]);
	if (e->run == 1)
	{
		e->cl.err = clEnqueueReadBuffer(e->queue, e->target_obj_buf, \
		CL_FALSE, 0, sizeof(t_hit), &e->target_obj, 0, NULL, &e->events[4]);
		e->run = 0;
	}
	if (e->cl.err != CL_SUCCESS)
	{
		opencl_print_error(e->cl.err);
		s_error("Error: Failed to read output array!", e);
	}
	return (0);
}*/

int			draw(t_env *e)
{
	t_cl *cl = &e->cl;

	opencl_set_args(e);
	/*t_cylinder *obj = e->gen_objects->mem;

	printf("--------------------------------CPU:\n");
	printf("t_cylinder:	%zu\n", sizeof(t_cylinder));
	printf("Size:		%i\n", obj->size);
	printf("Id:			%i\n", obj->id);
	printf("Pos:		%.2f %.2f %.2f\n", obj->pos.x, obj->pos.y, obj->pos.z);
	printf("Dir:		%.2f %.2f %.2f\n", obj->dir.x, obj->dir.y, obj->dir.z);
	printf("Diff:		%.2f %.2f %.2f\n", obj->diff.x, obj->diff.y, obj->diff.z);
	printf("Spec:		%.2f %.2f %.2f\n", obj->spec.x, obj->spec.y, obj->spec.z);
	printf("Color:		%i\n", obj->color);
	printf("Spec:		%.2f\n", obj->reflex);
	printf("*---------------------------------*\n");
	printf("Height:		%.2f\n", obj->height);
	printf("Base_dir:	%.2f %.2f %.2f\n", obj->base_dir.x, obj->base_dir.y, obj->base_dir.z);
	printf("Radius:		%.2f\n", obj->radius);
	printf("\n\n");*/

	//e->cl.err = clGetKernelWorkGroupInfo(KRT, e->device_id, \
	//		CL_KERNEL_WORK_GROUP_SIZE, sizeof(e->local), &e->local, NULL);

	cl_event event;

	event = 0;
	size_t newLo;
	size_t newGo;
	newGo = 1024;
	newLo = 1;

	/*cl->err = clEnqueueNDRangeKernel(cl->cq, cl->kernel, 1, NULL,
										&newGo,
										&newLo,
										0, NULL, &event);*/
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
			4 * 1024 * 720,
			e->frame->pix, 0, NULL, NULL);
	//get_imgptr(e);
	return (0);
}
