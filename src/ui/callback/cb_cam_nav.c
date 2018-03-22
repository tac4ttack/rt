#include "rt.h"

void		ui_cam_set_id(t_env *e)
{
	char	*cam_id;
	
	cam_id = ft_strjoin_frs2("CAMERA ", ft_itoa(e->scene->active_cam + 1));
	cam_id = ft_strjoin_frs1(cam_id, " / ");
	cam_id = ft_strjoin_free(cam_id, ft_itoa(e->scene->n_cams));
	gtk_label_set_text(GTK_LABEL(e->ui->cam_list_id_label), (gchar*)cam_id);
	free(cam_id);
}

void		cb_cam_nav_prev(GtkButton *btn, gpointer data)
{
	t_env	*e; 

	(void)btn;
	e = data;
	e->scene->active_cam = ((int)e->scene->active_cam - 1 \
	< 0 ? e->scene->n_cams - 1 : e->scene->active_cam - 1);
	ui_cam_set_id(e);	
	ui_cam_update(e);
}

void		cb_cam_nav_next(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	e->scene->active_cam = (e->scene->active_cam + 1 \
		< e->scene->n_cams ? e->scene->active_cam + 1 : 0);
	ui_cam_set_id(e);
	ui_cam_update(e);
}

void		cb_cam_nav_add(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
}

void		cb_cam_nav_del(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
}