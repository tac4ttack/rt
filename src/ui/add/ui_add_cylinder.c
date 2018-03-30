/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:56 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 19:59:57 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_add_cylinder(t_env *e)
{
	t_cylinder cylinder;

	cylinder.size = sizeof(t_cylinder);
	cylinder.id = e->gen_objects->length;
	cylinder.type = OBJ_CYLINDER;
	cylinder.pos.x = 0;
	cylinder.pos.y = 0;
	cylinder.pos.z = 0;
	cylinder.dir = cylinder.pos;
	cylinder.dir.z = 1;
	cylinder.dir = normalize_vect(cylinder.dir);
	cylinder.radius = 4;
	cylinder.color = rand();
	cylinder.height = 0;
	cylinder.diff.x = 0.42;
	cylinder.diff.y = 0.42;
	cylinder.diff.z = 0.42;
	cylinder.spec = cylinder.diff;
	cylinder.reflex = 0;
	cylinder.refract = 0;
	cylinder.opacity = 1;
	cylinder.base_dir = cylinder.dir;
	cylinder.base_dir = normalize_vect(cylinder.dir);
	e->gen_objects->add(e->gen_objects, (void*)&cylinder);
}
