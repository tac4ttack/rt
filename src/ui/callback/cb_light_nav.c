#include "rt.h"

void		ui_light_set_id(t_env *e)
{
	char	*cam_id;
	
	cam_id = ft_strjoin_frs2("CAMERA ", ft_itoa(e->scene->active_cam + 1));
	cam_id = ft_strjoin_frs1(cam_id, " / ");
	cam_id = ft_strjoin_free(cam_id, ft_itoa(e->scene->n_cams));
	gtk_label_set_text(GTK_LABEL(e->ui->cam_list_id_label), (gchar*)cam_id);
	free(cam_id);
}

void		cb_light_nav_prev(GtkButton *btn, gpointer data)
{
	t_env	*e;
	char	*light_id;

	(void)btn;
	e = data;
	light_id = NULL;

}

void		cb_light_nav_next(GtkButton *btn, gpointer data)
{
	t_env	*e;
	char	*light_id;

	(void)btn;
	e = data;
	light_id = NULL;
}

void		cb_light_nav_add(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
}

void		cb_light_nav_del(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
}

