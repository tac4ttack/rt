/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_toolbar.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:21 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 17:02:22 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cb_toolbar(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->tool_play_btn), \
	"clicked", G_CALLBACK(cb_play_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_stop_btn), \
	"clicked", G_CALLBACK(cb_stop_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_render_btn), \
	"clicked", G_CALLBACK(cb_render_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_export_btn), \
	"clicked", G_CALLBACK(cb_export_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_about_btn), \
	"clicked", G_CALLBACK(cb_about_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_save_btn), \
	"clicked", G_CALLBACK(cb_save_btn), (gpointer)e);
}

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
	e->ui->tool_save_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
														"tool_save_btn"));
	e->ui->tool_export_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
														"tool_export_btn"));
	e->ui->tool_about_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, \
														"tool_about_btn"));
	gtk_widget_set_sensitive(e->ui->tool_play_btn, FALSE);
	gtk_widget_set_sensitive(e->ui->tool_render_btn, FALSE);
	gtk_widget_set_sensitive(e->ui->tool_stop_btn, TRUE);
	init_cb_toolbar(e);
}
