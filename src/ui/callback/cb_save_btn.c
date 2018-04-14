/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_save_btn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:29 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/14 15:52:18 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_save_btn(GtkButton *btn, gpointer data)
{
	t_env	*e;
	char	*filename;
	
	(void)btn;
	filename = NULL;
	e = data;
	e->ui->save_window = gtk_file_chooser_dialog_new("Export scene to XML", \
								GTK_WINDOW(e->ui->main_window), \
								GTK_FILE_CHOOSER_ACTION_SAVE, \
								"Cancel", GTK_RESPONSE_CLOSE, \
								"Export", GTK_RESPONSE_OK, NULL);
	gtk_window_set_transient_for(GTK_WINDOW(e->ui->save_window), \
								GTK_WINDOW(e->ui->main_window));
	if (gtk_dialog_run(GTK_DIALOG(e->ui->save_window)) == GTK_RESPONSE_OK)
	{
		filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(\
												e->ui->save_window));
		xml_save_scene(e, filename);
		g_free(filename);
	}
	gtk_widget_destroy(e->ui->save_window);
}
