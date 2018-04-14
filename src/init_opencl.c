/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_opencl.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 19:23:33 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 20:11:26 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_kernel_buffer(t_env *e)
{
	if (!(e->cl->add_buffer(e->cl, WIDTH * HEIGHT * 4)))
		s_error("\x1b[2;31mError creation FRAMEBUFFER cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, e->gen_objects->mem_size)))
		s_error("\x1b[2;31mError creation OBJECTS cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(t_scene))))
		s_error("\x1b[2;31mError creation SCENE cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(t_cam) * NCAM)))
		s_error("\x1b[2;31mError creation CAMERAS cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, e->gen_lights->mem_size)))
		s_error("\x1b[2;31mError creation LIGHTS cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(int))))
		s_error("\x1b[2;31mError creation TARGETOBJ cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(unsigned int) * e->texture[0].width
													* e->texture[0].height)))
		s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(unsigned int) * e->texture[1].width
													* e->texture[1].height)))
		s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(unsigned int) * e->texture[2].width
													* e->texture[2].height)))
		s_error("\x1b[2;31mError creation cl_mem failed\x1b[0m", e);
	if (!(e->cl->add_buffer(e->cl, sizeof(unsigned int) * e->texture[3].width
													* e->texture[3].height)))
		s_error("\x1b[2;31mError creation cl_mem failed bite\x1b[0m", e);
}

static void		init_kernel_write_texture(t_env *e)
{
	if ((e->cl->err = clEnqueueWriteBuffer(e->cl->queue, e->cl->mem[6],
			CL_TRUE, 0,
			sizeof(unsigned int) * e->texture[0].width * e->texture[0].height,
							e->texture[0].pixel_array, 0, NULL, NULL)))
		s_error("Error: Failed to send text0 arguments to kernel!", e);
	if ((e->cl->err = clEnqueueWriteBuffer(e->cl->queue, e->cl->mem[7],
			CL_TRUE, 0,
			sizeof(unsigned int) * e->texture[1].width * e->texture[1].height,
							e->texture[1].pixel_array, 0, NULL, NULL)))
		s_error("Error: Failed to send text1 arguments to kernel!", e);
	if ((e->cl->err = clEnqueueWriteBuffer(e->cl->queue, e->cl->mem[8],
			CL_TRUE, 0,
			sizeof(unsigned int) * e->texture[2].width * e->texture[2].height,
							e->texture[2].pixel_array, 0, NULL, NULL)))
		s_error("Error: Failed to send text2 arguments to kernel!", e);
	if ((e->cl->err = clEnqueueWriteBuffer(e->cl->queue, e->cl->mem[9],
			CL_TRUE, 0,
			sizeof(unsigned int) * e->texture[3].width * e->texture[3].height,
							e->texture[3].pixel_array, 0, NULL, NULL)))
		s_error("Error: Failed to send text3 arguments to kernel!", e);
}

void			init_kernel(t_env *e)
{
	if (!(e->cl = cl_construct("./kernel/kernel.cl", WIDTH, HEIGHT,
	(e->scene->flag & OPTION_GPU) ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU)))
		s_error("\x1b[2;31mError t_cl creation failed\x1b[0m", e);
	init_kernel_buffer(e);
	init_kernel_write_texture(e);
}
