#include "rt.h"

void	init_gtk_win(t_env *e)
{
	e->ui->main_window = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
															"main_window"));
	e->ui->render = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
															"render"));
	gtk_widget_set_size_request(e->ui->render, e->scene->win_w, \
												e->scene->win_h);
	e->ui->pixbuf = gdk_pixbuf_new_from_data((const guchar *)e->pixel_data, \
							GDK_COLORSPACE_RGB, 1, 8, e->scene->win_w, \
							e->scene->win_h, e->scene->win_w * 4, NULL, NULL);
	e->ui->surface = NULL;
	e->ui->about_window = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
															"about_window"));
	gtk_window_set_transient_for(GTK_WINDOW(e->ui->about_window), \
											GTK_WINDOW(e->ui->main_window));
}
