/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:52 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 19:59:53 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_add_plane(t_env *e)
{
	t_plane plane;

	plane.size = sizeof(t_plane);
	plane.id = e->gen_objects->length;
	plane.type = OBJ_PLANE;
	plane.pos.x = 0;
	plane.pos.y = 0;
	plane.pos.z = 0;
	plane.normal = plane.pos;
	plane.normal.z = 1;
	plane.color = rand();
	plane.diff.x = 0.42;
	plane.diff.y = 0.42;
	plane.diff.z = 0.42;
	plane.spec = plane.diff;
	plane.reflex = 0;
	plane.refract = 0;
	plane.opacity = 1;
	e->gen_objects->add(e->gen_objects, (void*)&plane);
}
