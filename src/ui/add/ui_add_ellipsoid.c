/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_ellipsoid.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:54 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 12:51:00 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_add_ellipsoid(t_env *e)
{
	t_ellipsoid ellipsoid;

	ellipsoid.size = sizeof(t_ellipsoid);
	ellipsoid.id = e->gen_objects->length;
	ellipsoid.type = OBJ_ELLIPSOID;
	ellipsoid.pos.x = 0;
	ellipsoid.pos.y = 0;
	ellipsoid.pos.z = 0;
	ellipsoid.dir = ellipsoid.pos;
	ellipsoid.dir.z = 1;
	ellipsoid.flags = 0;
	ellipsoid.radius = 1;
	ellipsoid.color = rand();
	ellipsoid.diff.x = 0.42;
	ellipsoid.diff.y = 0.42;
	ellipsoid.diff.z = 0.42;
	ellipsoid.spec = ellipsoid.diff;
	ellipsoid.reflex = 0;
	ellipsoid.refract = 0;
	ellipsoid.opacity = 1;
	ellipsoid.axis_size.x = 2;
	ellipsoid.axis_size.y = 1;
	ellipsoid.axis_size.z = 2;
	e->gen_objects->add(e->gen_objects, (void*)&ellipsoid);
}
