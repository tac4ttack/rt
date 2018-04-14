/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cuda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 19:22:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 21:02:32 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <cuda.h>
#include <cuda_runtime.h>

int				draw(t_env *e)
{
	/*printf("CPU\n");
	printf("t_cam %zu\n", sizeof(t_cam));
	printf("t_scene %zu\n", sizeof(t_scene));
	printf("t_object %zu\n", sizeof(t_object));
	printf("t_gen %zu\n", sizeof(t_gen));
	printf("t_sphere %zu\n", sizeof(t_sphere));
	printf("t_light %zu\n", sizeof(t_light));
	printf("t_cylinder %zu\n", sizeof(t_cylinder));
	printf("t_sphere %zu\n", sizeof(t_sphere));
	printf("t_ellipsoid %zu\n", sizeof(t_ellipsoid));
	printf("t_plane %zu\n", sizeof(t_plane));
	printf("t_cone %zu\n", sizeof(t_cone));
	printf("t_cone %zu\n", sizeof(t_cone));
	printf("\n");*/
	render_cuda(e->cuda, e->pixel_data, &e->target,
					e->gen_objects,
					e->gen_lights,
					e->fps.u_time,
					e->scene,
					e->cameras);
	return (0);
}
