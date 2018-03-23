#include "rt.h"


void	cb_play_btn(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;
	e->ui->redraw = 1;
	gtk_widget_set_sensitive(e->ui->tool_play_btn, FALSE);
	gtk_widget_set_sensitive(e->ui->tool_stop_btn, TRUE);
}

void	cb_stop_btn(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;
	e->ui->redraw = 0;
	gtk_widget_set_sensitive(e->ui->tool_play_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->tool_stop_btn, FALSE);
}

void		gtk_export(GdkPixbuf *target, char *format, char *filename)
{
	GError		*error;

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

	(void)btn;
	e = data;
	ft_putendl("expoooooorteu");
	
	gtk_dialog_run(GTK_DIALOG(e->ui->file_export_window));
	gtk_widget_destroy(e->ui->file_export_window);
	
}
