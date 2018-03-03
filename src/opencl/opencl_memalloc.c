/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_memalloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:18:16 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/02 22:47:38 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

int			opencl_allocate_obj_memory(t_env *e)
{
	printf("JI\n");
	if (e->gen->unit_size)
		if (!(e->gen_mem = clCreateBuffer(e->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, e->gen->mem_size, e->gen->mem, &e->err)))
			return (opencl_builderrors(e, 7, e->err));
	return (0);
}

int			opencl_allocate_scene_memory(t_env *e)
{
	if (NCAM > 0)
		if (!(e->cameras_mem = clCreateBuffer(e->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_cam) * NCAM, e->cameras, &e->err)))
			return (opencl_builderrors(e, 7, e->err));
	if (NLIG > 0)
		if (!(e->lights_mem = clCreateBuffer(e->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_light) * NLIG, e->lights, &e->err)))
			return (opencl_builderrors(e, 7, e->err));
	if (opencl_allocate_obj_memory(e) != 0)
		return (EXIT_FAILURE);
	if (!(e->scene_mem = clCreateBuffer(e->context, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, sizeof(t_scene), e->scene, NULL)))
		return (opencl_builderrors(e, 7, e->err));
	return (0);
}
