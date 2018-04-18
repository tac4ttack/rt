/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cuda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 20:13:04 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/18 17:04:31 by fmessina         ###   ########.fr       */
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
		s_error("\x1b[2;31mError t_cuda cudaMalloc 0\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, e->gen_objects->mem_size)))
		s_error("\x1b[2;31mError t_cuda cudaMalloc 1\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, e->gen_lights->mem_size)))
		s_error("\x1b[2;31mError t_cuda cudaMalloc 2\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, sizeof(t_scene))))
		s_error("\x1b[2;31mError t_cuda cudaMalloc 3\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, sizeof(t_cam) * e->scene->n_cams)))
		s_error("\x1b[2;31mError t_cuda cudaMalloc 4\x1b[0m", e);
	if (!(cuda_add_buffer(e->cuda, sizeof(unsigned int))))
		s_error("\x1b[2;31mError t_cuda cudaMalloc 5\x1b[0m", e);
	// if (!(cuda_add_buffer(e->cuda, sizeof(unsigned int)
	// 						* e->texture[0].width * e->texture[0].height)))
	// 	s_error("\x1b[2;31mError t_cuda cudaMalloc 6\x1b[0m", e);
	//if (!(cuda_add_buffer(e->cuda, sizeof(unsigned int)
	//						* e->texture[1].width * e->texture[1].height)))
	//	s_error("\x1b[2;31mError t_cuda cudaMalloc 7\x1b[0m", e);
}

static void		init_kernel_write_texture(t_env *e)
{
	// if ((e->cuda->err = cudaMemcpy(e->cuda->mem[6], e->texture[0].pixel_array,
	// 		sizeof(unsigned int) * e->texture[0].width * e->texture[0].height,
	// 		cudaMemcpyHostToDevice)) != cudaSuccess)
	// {
	// 	cuda_error(e->cuda->err);
	// 	s_error("\x1b[2;31mError t_cuda cudaMemcpy 0 failed\x1b[0m", e);
	// }
	//if (!(cudaMemcpy(e->cuda->mem[7], e->texture[1].pixel_array,
	//		sizeof(unsigned int) * e->texture[1].width * e->texture[1].height,
	//		cudaMemcpyHostToDevice)))
	//	s_error("\x1b[2;31mError t_cuda creation failed\x1b[0m", e);
}

void			init_kernel(t_env *e)
{
	if (!(e->cuda = cuda_construct()))
		s_error("\x1b[2;31mError t_cuda creation failed\x1b[0m", e);
	init_kernel_buffer(e);
	init_kernel_write_texture(e);
}
