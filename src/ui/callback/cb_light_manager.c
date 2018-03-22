#include "rt.h"

void	cb_light_manage_add(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;
//	e->scene->n_cams++;
	gtk_widget_set_sensitive(e->ui->cam_nav_prev_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->cam_nav_next_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->cam_nav_del_btn, TRUE);
	ft_putendl("cam added");
}

void	cb_light_manage_del(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;
	if (e->scene->n_cams == 1)
		ft_putendl("you re not supposed to fall in this case, what did u du? :(((((");
	else
	{
		if (--e->scene->n_cams == 1)
		{
			gtk_widget_set_sensitive(e->ui->cam_nav_prev_btn, FALSE);
			gtk_widget_set_sensitive(e->ui->cam_nav_next_btn, FALSE);
			gtk_widget_set_sensitive(e->ui->cam_nav_del_btn, FALSE);
		}
		ft_putendl("cam deleted");

	}
}
