#include "rt.h"

gboolean cb_render_btnpress(GtkWidget *widget, GdkEvent  *event, gpointer data)
{
	(void)widget;
	(void)event;
	t_env *e;


	e = data;
//	gtk_widget_grab_focus(widget);
	ft_putendl("test btnpress");
	return TRUE;
}

gboolean cb_render_keypress(GtkWidget *widget, GdkEvent  *event, gpointer data)
{
	(void)widget;
	(void)event;
	t_env *e;

	e = data;
	ft_putendl("test keypress 1");
	return TRUE;
}


void		init_gtk(GtkApplication* app, gpointer data)
{
	t_env *e;

	e = data;
	(void)app;

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
	e->ui->pixbuf = gdk_pixbuf_new_from_data((const guchar *)e->pixel_data, GDK_COLORSPACE_RGB, 1, 8, e->win_w, e->win_h, e->win_w * 4, NULL, NULL);
	e->ui->surface = NULL;
	g_signal_connect(e->ui->render,"configure-event", G_CALLBACK(cb_configure_draw_area), (gpointer)e);
	g_signal_connect(e->ui->render, "draw", G_CALLBACK(cb_draw_render), (gpointer)e);


	// signals and shit
	//gtk_signal_connect(GTK_OBJECT(e->ui->render));
//	g_signal_connect(GTK_WIDGET(e->ui->left_panel_scroll_win), "key-press-event", G_CALLBACK(cb_render_keypress1), (gpointer)e);
//	g_signal_connect(GTK_WIDGET(e->ui->left_panel_viewport), "key-press-event", G_CALLBACK(cb_render_keypress2), (gpointer)e);
	gtk_widget_add_events (e->ui->render, GDK_BUTTON_PRESS_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "button-press-event", G_CALLBACK(cb_render_btnpress), (gpointer)e);
	gtk_widget_add_events (e->ui->render, GDK_KEY_PRESS_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "key-press-event", G_CALLBACK(cb_render_keypress), (gpointer)e);
	
	
	// init and activate all preset signals from template
	gtk_builder_connect_signals(e->ui->builder, NULL);
	
	// free the builder
	g_object_unref(e->ui->builder);

	gtk_widget_show_all(e->ui->main_window);

	g_idle_add(gtk_main_loop, (gpointer)e);

	gtk_main();
}
