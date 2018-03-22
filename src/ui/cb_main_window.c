#include "rt.h"


void	cb_main_window_resize(GtkContainer *box, gpointer data)
{
	t_env *e;
	cl_int2 zone;

	e = data;
	(void)box;
	zone.x = gtk_widget_get_allocated_width(e->ui->left_panel_scroll);
	zone.y = gtk_widget_get_allocated_height(e->ui->left_panel_scroll);
	if ((int)e->scene->win_w <= zone.x && (int)e->scene->win_h <= zone.y)
	{
		e->ui->render_pos.w = (zone.x / 2) - (e->scene->win_w / 2);
		e->ui->render_pos.x = (zone.y / 2) - (e->scene->win_h / 2) + 42;
		e->ui->render_pos.y = e->scene->win_w;
		e->ui->render_pos.z = e->scene->win_h;
	}
}
		