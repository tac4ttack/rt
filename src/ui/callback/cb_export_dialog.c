/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_export_dialog.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:00 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/14 15:52:10 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		gtk_export(GdkPixbuf *target, char *format, char *filename)
{
	GError	*error;

	error = NULL;
	gdk_pixbuf_save(target, filename, format, &error, NULL);
	g_assert_no_error(error);
	ft_putstr("\x1b[1;29mFile\x1b[0m \x1b[1;33m");
	ft_putstr(filename);
	ft_putendl("\x1b[0m\x1b[1;29m successfully exported!\x1b[0m");
}

void		cb_export_btn(GtkButton *btn, gpointer data)
{
	t_env	*e;
	char	*filename;

	(void)btn;
	e = data;
	filename = NULL;
	e->ui->export_window = gtk_file_chooser_dialog_new("Export render to PNG", \
								GTK_WINDOW(e->ui->main_window), \
								GTK_FILE_CHOOSER_ACTION_SAVE, \
								"Cancel", GTK_RESPONSE_CLOSE, \
								"Export", GTK_RESPONSE_OK, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(e->ui->export_window), \
								GTK_WINDOW(e->ui->main_window));
	if (gtk_dialog_run(GTK_DIALOG(e->ui->export_window)) == GTK_RESPONSE_OK)
	{
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(\
												e->ui->export_window));
		gtk_export(e->ui->pixbuf, "png", filename);
		g_free(filename);
	}
	gtk_widget_destroy(e->ui->export_window);
}
