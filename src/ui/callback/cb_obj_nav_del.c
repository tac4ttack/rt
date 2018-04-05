/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_nav_del.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:21 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:29:16 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_nav_del(GtkButton *btn, gpointer data)
{
	t_env		*e;
	t_object	*obj;

	(void)btn;
	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	obj = e->gen_objects->mem + e->target;
	e->gen_objects->remove_mem_index(e->gen_objects, e->target);
	if (e->gen_objects->length == 1)
	{
		gtk_widget_set_sensitive(e->ui->obj_nav_prev_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->obj_nav_next_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->obj_nav_del_btn, FALSE);
	}
	if (!(cl_replace_buffer(e->cl, e->gen_objects->mem_size, 1)))
		s_error("\x1b[2;31mFailed replacing objects buffer\x1b[0m", e);
	e->target = -1;
	if (e->gen_objects->length < 2)
	{
		gtk_widget_set_sensitive(e->ui->obj_nav_prev_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->obj_nav_next_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->obj_nav_del_btn, FALSE);
	}
	ui_obj_update(e, obj);
	ui_obj_jump_list(e);
}
