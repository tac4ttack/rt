/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_add_torus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 19:59:37 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 19:59:38 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_add_torus(t_env *e)
{
	t_torus torus;

	torus.size = sizeof(t_torus);
	torus.id = e->gen_objects->length;
	torus.type = OBJ_TORUS;
	torus.pos.x = 0;
	torus.pos.y = 0;
	torus.pos.z = 0;
	torus.dir = torus.pos;
	torus.dir.z = 1;
	torus.lil_radius = 4;
	torus.big_radius = 16;
	torus.color = rand();
	torus.diff.x = 0.42;
	torus.diff.y = 0.42;
	torus.diff.z = 0.42;
	torus.spec = torus.diff;
	torus.reflex = 0;
	torus.refract = 0;
	torus.opacity = 1;
	e->gen_objects->add(e->gen_objects, (void*)&torus);
}
