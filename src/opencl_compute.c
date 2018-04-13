/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_compute.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:40:38 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/13 19:51:41 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
/*
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

int				opencl_draw(t_env *e)
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
*/

typedef struct			s_test
{
	unsigned int		id;
	t_float3				pos;
	t_float3				dir;
	float				fov;
	float				pitch;
	float				yaw;
	float				roll;
}						t_test;

int				opencl_draw(t_env *e)
{
	(void)e;
	bzero(e->pixel_data, (e->scene->win_w * e->scene->win_h) *4);
	//printf("CPU %x\n", ((t_sphere *)e->gen_objects->mem)->color);
	
	render_cuda(&e->cuda, e->pixel_data, &e->target,
					e->gen_objects,
					e->gen_lights,
					e->fps.u_time,
					e->scene,
					e->cameras);

	// printf("CPU\n");
	// printf("t_cam %zu\n", sizeof(t_cam));
	// printf("t_scene %zu\n", sizeof(t_scene));
	// printf("t_object %zu\n", sizeof(t_object));
	// printf("t_gen %zu\n", sizeof(t_gen));
	// printf("t_sphere %zu\n", sizeof(t_sphere));
	// printf("t_light %zu\n", sizeof(t_light));
	// printf("t_cylinder %zu\n", sizeof(t_cylinder));
	// printf("t_sphere %zu\n", sizeof(t_sphere));
	// printf("t_ellipsoid %zu\n", sizeof(t_ellipsoid));
	// printf("t_plane %zu\n", sizeof(t_plane));
	// printf("t_cone %zu\n", sizeof(t_cone));
	// printf("t_cone %zu\n", sizeof(t_cone));
	// printf("t_box %zu\n", sizeof(t_box));
	// printf("FT_FLOAT3 %zu\n", sizeof(FT_FLOAT3));
	// printf("t_float3 %zu\n", sizeof(t_float3));
	// printf("t_test %zu\n", sizeof(t_test));
	// printf("\n");

//	for (int i = (e->scene->win_w * e->scene->win_h) - 10; i < (int)(e->scene->win_w * e->scene->win_h); i++) {
/*	for (int i = 0; i < 10; i++) {
		printf("%x\n", ((int *)e->pixel_data)[i]);
		//e->pixel_data[i] = 0xFF000000;
	}*/
 	return (0);
}


// if (e->scene->flag & OPTION_RUN)
// 	{
// 		cl->err = clEnqueueReadBuffer(cl->queue, cl->mem[5], CL_TRUE, 0,
// 			sizeof(int),
// 			&e->target, 0, NULL, NULL);
// 		e->scene->flag ^= OPTION_RUN;
// 	}
