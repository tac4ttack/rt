#include "rt.h"

/*void		cb_light_nav_prev(GtkButton *btn, gpointer data)
{
	t_env	*e;
	char	*light_id;

	(void)btn;
	e = data;
	light_id = NULL;

	e->scene->active_cam = ((int)e->scene->active_cam - 1 \
	< 0 ? e->scene->n_cams - 1 : e->scene->active_cam - 1);

	light_id = ft_strjoin_frs2("LIGHT #", ft_itoa(e->scene->n_lights));
	
	gtk_label_set_text(GTK_LABEL(e->ui->light_list_id_label), (gchar*)light_id);
	free(light_id);
	ui_light_update(e);
}

void		cb_light_nav_next(GtkButton *btn, gpointer data)
{
	t_env	*e;
	char	*light_id;

	(void)btn;
	e = data;
	light_id = NULL;

	e->scene->active_cam = (e->scene->active_cam + 1 \
		< e->scene->n_cams ? e->scene->active_cam + 1 : 0);

	light_id = ft_strjoin_frs2("LIGHT #", ft_itoa(e->scene->n_lights));

	gtk_label_set_text(GTK_LABEL(e->ui->light_list_id_label), (gchar*)light_id);
	free(light_id)
	ui_light_update(e);
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
*/
