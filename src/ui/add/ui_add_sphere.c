/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:42 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 19:59:43 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_add_sphere(t_env *e)
{
	t_sphere sphere;

	sphere.size = sizeof(t_sphere);
	sphere.id = e->gen_objects->length;
	sphere.type = OBJ_SPHERE;
	sphere.pos.x = 0;
	sphere.pos.y = 0;
	sphere.pos.z = 0;
	sphere.dir = sphere.pos;
	sphere.dir.z = 1;
	sphere.radius = 4;
	sphere.color = rand();
	sphere.diff.x = 0.42;
	sphere.diff.y = 0.42;
	sphere.diff.z = 0.42;
	sphere.spec = sphere.diff;
	sphere.reflex = 0;
	sphere.refract = 0;
	sphere.opacity = 1;
	e->gen_objects->add(e->gen_objects, (void*)&sphere);
}
