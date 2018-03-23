#include "rt.h"


void	cb_play_btn(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;
	e->ui->redraw = 1;
	gtk_widget_set_sensitive(e->ui->tool_play_btn, FALSE);
	gtk_widget_set_sensitive(e->ui->tool_render_btn, FALSE);
	gtk_widget_set_sensitive(e->ui->tool_stop_btn, TRUE);
}

void	cb_stop_btn(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;
	e->ui->redraw = 0;
	gtk_widget_set_sensitive(e->ui->tool_play_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->tool_render_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->tool_stop_btn, FALSE);
}

void	cb_render_btn(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;
//	e->ui->redraw = 0;
//	gtk_widget_set_sensitive(e->ui->tool_play_btn, TRUE);
//	gtk_widget_set_sensitive(e->ui->tool_stop_btn, FALSE);
}
