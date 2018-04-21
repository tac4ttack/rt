/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_cuda.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <ntoniolo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 19:22:54 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/21 20:49:20 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <cuda.h>
#include <cuda_runtime.h>

int				draw(t_env *e)
{
	render_cuda(e->cuda, e->pixel_data, &e->target,
					e->gen_objects,
					e->gen_lights,
					e->fps.u_time,
					e->scene,
					e->cameras,
					&e->scene->tex[0],
					&e->scene->tex[1],
					&e->scene->tex[2],
					&e->scene->tex[3],
					&e->scene->tex[4]);
	return (0);
}
