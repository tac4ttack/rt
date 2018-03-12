#include "rt.h"

gboolean cb_draw_test(GtkWidget *widget, GdkEvent  *event, gpointer data)
{
	t_env *e;
	cairo_t				*cr;

	e = data;
	(void)event;
	(void)widget;
	cr = cairo_create(e->ui->surface);
	update_fps(&e->fps);
	opencl_draw(e);
	ft_putendl("im in drawtest");
	// 1ere methode
	gdk_cairo_set_source_pixbuf(cr, e->ui->pixbuf, 0, 0);

	// 2nde methode
//	if (e->ui->surface)
//		cairo_surface_destroy(e->ui->surface);
//	e->ui->surface = gdk_cairo_surface_create_from_pixbuf (e->ui->pixbuf, 1, NULL);
//	cairo_set_source_surface(cr, e->ui->surface, 0, 0);

	cairo_paint(cr);
	return FALSE;
}


void		init_gtk(GtkApplication* app, gpointer data)
{
	t_env *e;

	e = data;
	(void)app;
	ft_putendl("im in gtk init");
	
//	// css loading
//	e->ui->css = gtk_css_provider_new();
//	gtk_css_provider_load_from_path(e->ui->css, "./theme/gtk-dark.css", NULL);

	// init the builder and load the template
	e->ui->builder = gtk_builder_new();
	gtk_builder_add_from_file(e->ui->builder, "./theme/rt_ui.glade", NULL);

	// init and connect the main window
	e->ui->main_window = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_window"));
	gtk_window_set_title(GTK_WINDOW(e->ui->main_window), "RT");
	g_signal_connect(e->ui->main_window, "destroy", G_CALLBACK(gtk_quit), (gpointer)e);

	// init all widget in order
	e->ui->main_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_box"));
	e->ui->main_panels = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_panels"));
	e->ui->left_panel_scroll_win = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "left_panel_scroll_win"));
	e->ui->left_panel_viewport = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "left_panel_viewport"));
	e->ui->right_panel = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "right_panel"));
	e->ui->tool_bar = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_bar"));
	e->ui->status_bar = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "status_bar"));

	// init render shit
	e->ui->render = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "render"));
	gtk_widget_set_app_paintable(e->ui->render, TRUE);
	e->ui->pixbuf = gdk_pixbuf_new_from_data((const guchar *)e->pixel_data, GDK_COLORSPACE_RGB, 1, 8, e->win_w, e->win_h, e->win_w * 4, NULL, NULL);
	e->ui->surface = NULL;
	g_signal_connect(e->ui->render,"configure-event", G_CALLBACK(cb_configure_draw_area), (gpointer)e);
	g_signal_connect(e->ui->render, "draw", G_CALLBACK(cb_draw_render), (gpointer)e);
//	g_signal_connect(e->ui->render, "event", G_CALLBACK(cb_draw_test), (gpointer)e);



//	gtk_image_set_from_pixbuf(GTK_IMAGE(e->ui->render), e->ui->pixbuf);
	

	// init and activate all preset signals from template
	gtk_builder_connect_signals(e->ui->builder, NULL);
	
	// free the builder
	g_object_unref(e->ui->builder);

	gtk_widget_show_all(e->ui->main_window);
	gtk_main();
}
