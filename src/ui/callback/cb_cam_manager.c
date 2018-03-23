#include "rt.h"

void	cb_cam_manage_add(GtkButton *btn, gpointer data)
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

void	cb_cam_manage_del(GtkButton *btn, gpointer data)
{
	int		i;
	int		j;
	t_env	*e;
	t_cam	*new_cams;

	(void)btn;
	i = 0;
	j = 0;
	e = data;
	new_cams = NULL;
	if (e->scene->n_cams == 1)
		ft_putendl("why did u du dis? :(((((");
	else
	{
		if (!(new_cams = malloc(sizeof(t_cam) * (NCAM - 1))))
			s_error("\x1b[1;31mCan't recreate cameras array\x1b[0m", e);

		while (i < (int)NCAM)
		{
			if (i == (int)e->scene->active_cam)
				i++;
			else
			{
				ft_memcpy(&new_cams[j], &e->cameras[i], sizeof(t_cam));
				j++;
				i++;
			}
		}
		free(e->cameras);
		e->cameras = new_cams;
		if (--e->scene->n_cams == 1)
		{
			gtk_widget_set_sensitive(e->ui->cam_nav_prev_btn, FALSE);
			gtk_widget_set_sensitive(e->ui->cam_nav_next_btn, FALSE);
			gtk_widget_set_sensitive(e->ui->cam_nav_del_btn, FALSE);
		}
		if (!(cl_replace_buffer(e->cl, sizeof(t_cam) * NCAM, 3)))
			s_error("\x1b[2;31mError creation new cameras buffer cl_mem failed\x1b[0m", e);
		e->scene->active_cam--;
		ui_cam_set_id(e);	
		ui_cam_update(e);
	}
}
