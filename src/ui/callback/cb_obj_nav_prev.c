/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_nav_prev.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:27 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:29:11 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_nav_prev(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;
	int			obj_index;

	(void)btn;
	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	obj = e->gen_objects->mem + e->target;
	obj_index = gen_get_ptr_index(e->gen_objects, obj);
	if (obj_index == 0)
	{
		obj = (t_object*)gen_get_index_ptr(e->gen_objects, \
											e->gen_objects->length - 1);
		e->target = (void*)obj - e->gen_objects->mem;
	}
	else
		obj = (t_object*)gen_get_index_ptr(e->gen_objects, obj_index - 1);
	ui_obj_update(e, obj);
}
