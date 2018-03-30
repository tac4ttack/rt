#include "rt.h"

void	init_cb_main(t_env *e)
{
	g_signal_connect(e->ui->main_window, "destroy", \
	G_CALLBACK(gtk_quit), (gpointer)e);
	g_signal_connect(e->ui->main_window, "check-resize", \
	G_CALLBACK(cb_render_update_size), (gpointer)e);
	g_signal_connect(e->ui->render, "configure-event", \
	G_CALLBACK(cb_configure_draw_area), (gpointer)e);
	g_signal_connect(e->ui->render, "draw", \
	G_CALLBACK(cb_render_draw), (gpointer)e);
	gtk_widget_add_events(e->ui->render, GDK_BUTTON_PRESS_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "button-press-event", \
	G_CALLBACK(cb_render_btnpress), (gpointer)e);
	gtk_widget_add_events(e->ui->render, GDK_KEY_PRESS_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "key-press-event", \
	G_CALLBACK(cb_render_keypress), (gpointer)e);
	gtk_widget_add_events(e->ui->render, GDK_KEY_RELEASE_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "key-release-event", \
	G_CALLBACK(cb_render_keyrelease), (gpointer)e);
	gtk_widget_grab_focus(e->ui->render);
	gtk_builder_connect_signals(e->ui->builder, NULL);
}
