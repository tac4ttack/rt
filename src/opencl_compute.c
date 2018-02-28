/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:40:38 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/28 13:27:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		opencl_set_args(t_env *e)
{
	e->err = 0;
	e->err = clSetKernelArg(KRT, 0, sizeof(cl_mem), &e->frame_buffer);
	e->err |= clSetKernelArg(KRT, 1, sizeof(cl_mem), &e->target_obj_buf);
	e->err |= clSetKernelArg(KRT, 2, sizeof(cl_mem), &e->scene_mem);
	e->err |= clSetKernelArg(KRT, 3, sizeof(cl_mem), &e->cameras_mem);
	e->err |= clSetKernelArg(KRT, 4, sizeof(cl_mem), &e->cones_mem);
	e->err |= clSetKernelArg(KRT, 5, sizeof(cl_mem), &e->cylinders_mem);
	e->err |= clSetKernelArg(KRT, 6, sizeof(cl_mem), &e->lights_mem);
	e->err |= clSetKernelArg(KRT, 7, sizeof(cl_mem), &e->planes_mem);
	e->err |= clSetKernelArg(KRT, 8, sizeof(cl_mem), &e->spheres_mem);
	e->err |= clSetKernelArg(KRT, 9, sizeof(t_scene), NULL);
	e->err |= clSetKernelArg(KRT, 10, sizeof(t_cam) * NCAM + 4, NULL);
	e->err |= clSetKernelArg(KRT, 11, sizeof(t_cone) * NCON + 4, NULL);
	e->err |= clSetKernelArg(KRT, 12, sizeof(t_cylinder) * NCYL + 4, NULL);
	e->err |= clSetKernelArg(KRT, 13, sizeof(t_light) * NLIG + 4, NULL);
	e->err |= clSetKernelArg(KRT, 14, sizeof(t_plane) * NPLA + 4, NULL);
	e->err |= clSetKernelArg(KRT, 15, sizeof(t_sphere) * NSPH + 4, NULL);
	e->err |= clSetKernelArg(KRT, 16, sizeof(float), &(e->fps.u_time));
	if (e->err != CL_SUCCESS)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to send arguments to kernel!", e);
	}
}

/*
** the "CL_TRUE" flag blocks the read operation until
** 	all work items have finished their computation
*/

int			get_imgptr(t_env *e)
{
	clFinish(e->queue);
	e->err = clEnqueueReadBuffer(e->queue, e->frame_buffer, CL_TRUE, 0, \
			(e->count * 4), e->frame->pix, 0, NULL, &e->events[3]);
	if (e->run == 1)
	{
		e->err = clEnqueueReadBuffer(e->queue, e->target_obj_buf, \
		CL_FALSE, 0, sizeof(t_hit), &e->target_obj, 0, NULL, &e->events[4]);
		e->run = 0;
	}
	if (e->err != CL_SUCCESS)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to read output array!", e);
	}
	return (0);
}

void		opencl_sepia(t_env *e)
{
	const size_t	g[2] = {WIDTH, HEIGHT};

	e->err = 0;
	e->err = clEnqueueReadBuffer(e->queue, e->frame_buffer, CL_TRUE, 0, \
			(e->count * 4), e->frame->pix, 1, &e->events[0], &e->events[3]);
	(e->err != 0 ? opencl_print_error(e->err) : 0);
	if (!(e->frame_buffer = clCreateBuffer(e->context, CL_MEM_WRITE_ONLY | \
	CL_MEM_COPY_HOST_PTR, e->count * 4, e->frame->pix, &e->err)))
		opencl_builderrors(e, 7, e->err);
	e->err |= clSetKernelArg(KSP, 0, sizeof(cl_mem), &e->frame_buffer);
	(e->err != 0 ? opencl_print_error(e->err) : 0);
	e->err |= clSetKernelArg(KSP, 1, sizeof(int), &e->scene->win_w);
	(e->err != 0 ? opencl_print_error(e->err) : 0);
	e->err |= clSetKernelArg(KSP, 2, sizeof(int), &e->scene->win_h);
	(e->err != 0 ? opencl_print_error(e->err) : 0);
	e->err |= clEnqueueNDRangeKernel(e->queue, KSP, 2, NULL, g, NULL, 1, \
									&e->events[3], &e->events[1]);
	if (e->err)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to execute Sepia kernel!\n", e);
	}
	get_imgptr(e);
}

void		opencl_black_and_white(t_env *e)
{
	const size_t	g[2] = {WIDTH, HEIGHT};

	e->err = 0;
	e->err = clEnqueueReadBuffer(e->queue, e->frame_buffer, CL_TRUE, 0, \
			(e->count * 4), e->frame->pix, 1, &e->events[0], &e->events[3]);
	(e->err != 0 ? opencl_print_error(e->err) : 0);
	if (!(e->frame_buffer = clCreateBuffer(e->context, CL_MEM_WRITE_ONLY | \
	CL_MEM_COPY_HOST_PTR, e->count * 4, e->frame->pix, &e->err)))
		opencl_builderrors(e, 7, e->err);
	e->err |= clSetKernelArg(KBW, 0, sizeof(cl_mem), &e->frame_buffer);
	(e->err != 0 ? opencl_print_error(e->err) : 0);
	e->err |= clSetKernelArg(KBW, 1, sizeof(int), &e->scene->win_w);
	(e->err != 0 ? opencl_print_error(e->err) : 0);
	e->err |= clSetKernelArg(KBW, 2, sizeof(int), &e->scene->win_h);
	(e->err != 0 ? opencl_print_error(e->err) : 0);
	e->err |= clEnqueueNDRangeKernel(e->queue, KBW, 2, NULL, g, NULL, 1, \
									&e->events[3], &e->events[2]);
	if (e->err)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to execute Black & White kernel!\n", e);
	}
	get_imgptr(e);
}

int			draw(t_env *e)
{
	const size_t	g[2] = {WIDTH, HEIGHT};

	opencl_set_args(e);
	e->err = clGetKernelWorkGroupInfo(KRT, e->device_id, \
			CL_KERNEL_WORK_GROUP_SIZE, sizeof(e->local), &e->local, NULL);
	if (e->err != CL_SUCCESS)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to retrieve kernel work group info!", e);
	}
	e->err = clEnqueueNDRangeKernel(e->queue, KRT, 2, NULL, \
			g, NULL, 0, NULL, &e->events[0]);
	if (e->err)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to execute Ray_trace kernel!\n", e);
	}
	if (e->scene->flag & OPTION_SEPIA)
		opencl_sepia(e);
	if (e->scene->flag & OPTION_BW)
		opencl_black_and_white(e);
	get_imgptr(e);
	return (0);
}

void		opencl_close(t_env *e)
{
	clReleaseMemObject(e->frame_buffer);
	clReleaseMemObject(e->target_obj_buf);
	clReleaseProgram(e->program);
	clReleaseKernel(KRT);
	clReleaseKernel(KSP);
	clReleaseKernel(KBW);
	clReleaseCommandQueue(e->queue);
	clReleaseContext(e->context);
}
