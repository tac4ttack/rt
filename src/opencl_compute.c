/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:40:38 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/05 19:36:05 by fmessina         ###   ########.fr       */
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
			(e->count * 4), e->frame_pixel_data, 0, NULL, &e->events[1]);
	if (e->run == 1)
	{
		e->err = clEnqueueReadBuffer(e->queue, e->target_obj_buf, \
		CL_FALSE, 0, sizeof(t_hit), &e->target_obj, 0, NULL, &e->events[2]);
		e->run = 0;
	}
	if (e->err != CL_SUCCESS)
	{
		opencl_print_error(e->err);
		s_error("Error: Failed to read output array!", e);
	}
	return (0);
}

int			opencl_draw(t_env *e)
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
	get_imgptr(e);
	return (0);
}

void		opencl_close(t_env *e)
{
	clReleaseMemObject(e->frame_buffer);
	clReleaseMemObject(e->target_obj_buf);
	clReleaseProgram(e->program);
	clReleaseKernel(KRT);
	clReleaseCommandQueue(e->queue);
	clReleaseContext(e->context);
}
