/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   opencl_memalloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:18:16 by adalenco          #+#    #+#             */
/*   Updated: 2018/02/26 19:18:17 by adalenco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			opencl_allocate_obj_memory(t_env *e)
{
	if (NCON > 0)
		if (!(e->cones_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_cone) * NCON, e->cones, &e->err)))
			return (opencl_builderrors(e, 7, e->err));
	if (NCYL > 0)
		if (!(e->cylinders_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_cylinder) * NCYL, e->cylinders, &e->err)))
			return (opencl_builderrors(e, 7, e->err));
	if (NPLA > 0)
		if (!(e->planes_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_plane) * NPLA, e->planes, &e->err)))
			return (opencl_builderrors(e, 7, e->err));
	if (NSPH > 0)
		if (!(e->spheres_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_sphere) * NSPH, e->spheres, &e->err)))
			return (opencl_builderrors(e, 7, e->err));
	return (0);
}

int			opencl_allocate_scene_memory(t_env *e)
{
	if (NCAM > 0)
		if (!(e->cameras_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_cam) * NCAM, e->cameras, &e->err)))
			return (opencl_builderrors(e, 7, e->err));
	if (NLIG > 0)
		if (!(e->lights_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_light) * NLIG, e->lights, &e->err)))
			return (opencl_builderrors(e, 7, e->err));
	if (opencl_allocate_obj_memory(e) != 0)
		return (EXIT_FAILURE);
	if (!(e->scene_mem = clCreateBuffer(e->context, CL_MEM_READ_ONLY | \
		CL_MEM_COPY_HOST_PTR, sizeof(t_scene), e->scene, NULL)))
		return (opencl_builderrors(e, 7, e->err));
	return (0);
}
