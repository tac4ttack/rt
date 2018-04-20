/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_leaks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/20 12:15:55 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/20 12:15:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gtk/gtk.h"

static void			activate(GtkApplication *app, gpointer user_data)
{
	GtkWidget		*window;
	GtkWidget		*label;

	window = gtk_application_window_new(app);
	gtk_window_set_title(GTK_WINDOW(window), "Minimal GTK");
	gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
	label = gtk_label_new("Some men just want to watch the world burn.");
	gtk_container_add(GTK_CONTAINER(window), label);
	gtk_widget_show_all(window);
}

int					main(int argc, char **argv)
{
	GtkApplication	*app;
	int				app_status;

	app = gtk_application_new("com.github.laerne.minimal_gtk", \
								G_APPLICATION_FLAGS_NONE);
	g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
	app_status = g_application_run(G_APPLICATION(app), argc, argv);
	g_object_unref(app);
	return (app_status);
}
