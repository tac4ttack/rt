/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_nav_next.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:24 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:38:08 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_nav_next(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;
	int			obj_index;

	(void)btn;
	e = data;
	obj = e->gen_objects->mem + e->target;
	obj_index = gen_get_ptr_index(e->gen_objects, obj);
	if (obj_index + 1 == (int)(e->gen_objects->length))
		e->target = 0;
	else
		e->target = e->target + obj->size;
	obj = e->gen_objects->mem + e->target;
	ui_obj_update(e, obj);
}
