#include "rt.h"

void	init_gtk_toolbar(t_env *e)
{
	e->ui->tool_fps_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
														"tool_fps_label"));
	e->ui->tool_play_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
														"tool_play_btn"));
	e->ui->tool_stop_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
														"tool_stop_btn"));
	e->ui->tool_render_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
														"tool_render_btn"));
	e->ui->tool_export_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
														"tool_export_btn"));
	e->ui->tool_about_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
														"tool_about_btn"));
	gtk_widget_set_sensitive(e->ui->tool_play_btn, FALSE);
	gtk_widget_set_sensitive(e->ui->tool_render_btn, FALSE);
	gtk_widget_set_sensitive(e->ui->tool_stop_btn, TRUE);
}
