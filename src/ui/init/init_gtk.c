/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:17 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 14:27:27 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		init_gtk(GtkApplication *app, gpointer data)
{
	t_env *e;

	e = data;
	(void)app;
	init_gtk_css(e);
	e->ui->builder = gtk_builder_new();
	gtk_builder_add_from_file(e->ui->builder, "./theme/rt_ui.glade", NULL);
	init_gtk_win(e);
	init_gtk_object(e);
	init_gtk_scene(e);
	init_gtk_cam(e);
	init_gtk_light(e);
	init_gtk_toolbar(e);
	init_cb_main(e);
	init_cb_scene(e);
	init_cb_cam(e);
	init_cb_light(e);
	init_cb_object(e);
	g_object_unref(e->ui->builder);
	gtk_widget_show_all(e->ui->main_window);
	ui_obj_jump_list(e);
	ui_obj_update(e, e->gen_objects->mem + e->target);
	g_idle_add(gtk_main_loop, (gpointer)e);
	gtk_main();
}
