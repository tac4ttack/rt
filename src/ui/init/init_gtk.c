/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:17 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/21 18:50:27 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_gtk_widgets(t_env *e)
{
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
}

void		init_gtk(GtkApplication *app, gpointer data)
{
	t_env *e;

	e = data;
	(void)app;
	init_gtk_css(e);
	e->ui->builder = gtk_builder_new();
	if (gtk_builder_add_from_file(e->ui->builder, "./theme/rt_ui.glade", \
														&e->ui->error) == 0)
	{
		ft_putendl(e->ui->error->message);
		s_error("\x1b[1;31mError opening UI theme file\x1b[0m", e);
	}

	init_gtk_widgets(e);
	g_object_unref(e->ui->builder);
	e->ui->builder = NULL;
	gtk_widget_show_all(e->ui->main_window);
	ui_obj_jump_list(e);
	ui_obj_update(e, e->gen_objects->mem + e->target);
	ft_putendl("\x1b[1;29mUI successfully loaded!\n\x1b[0m");
	g_idle_add(gtk_main_loop, (gpointer)e);
	gtk_main();
}
