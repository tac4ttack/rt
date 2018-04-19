/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cuda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 20:13:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/19 12:22:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "t_cuda.h"
#include <cuda.h>
#include <cuda_runtime.h>

static void		init_kernel_buffer(t_env *e)
{
	if (!(cuda_add_buffer(e->cuda,
						e->scene->win_w * e->scene->win_h * sizeof(int))))
		s_error("\x1b[2;31mError t_cuda cudaMalloc OUTPUT buffer\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, e->gen_objects->mem_size)))
		s_error("\x1b[2;31mError t_cuda cudaMalloc OBJECTS data\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, e->gen_lights->mem_size)))
		s_error("\x1b[2;31mError t_cuda cudaMalloc LIGHTS data\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, sizeof(t_scene))))
		s_error("\x1b[2;31mError t_cuda cudaMalloc SCENE\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, sizeof(t_cam) * e->scene->n_cams)))
		s_error("\x1b[2;31mError t_cuda cudaMalloc CAMS data\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, sizeof(unsigned int))))
		s_error("\x1b[2;31mError t_cuda cudaMalloc TARGET data\x1b[0m", e);
}

void			init_kernel(t_env *e)
{
	if (!(e->cuda = cuda_construct()))
		s_error("\x1b[2;31mError t_cuda creation failed\x1b[0m", e);
	init_kernel_buffer(e);
	texture_init(e);
}
