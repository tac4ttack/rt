#include "rt.h"

void		ui_light_set_id(t_env *e)
{
	char	*light_id;
	
	light_id = ft_strjoin_frs2("LIGHT ", ft_itoa(e->ui->light_selector + 1));
	light_id = ft_strjoin_frs1(light_id, " / ");
	light_id = ft_strjoin_free(light_id, ft_itoa(e->scene->n_lights));
	gtk_label_set_text(GTK_LABEL(e->ui->light_list_id_label), (gchar*)light_id);
	free(light_id);
}

void		cb_light_nav_prev(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	e->ui->light_selector = ((int)e->ui->light_selector - 1 \
	< 0 ? e->scene->n_lights - 1 : e->ui->light_selector - 1);
	ui_light_set_id(e);	
	ui_light_update(e);
}

void		cb_light_nav_next(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	e->ui->light_selector = (e->ui->light_selector + 1 \
	< e->scene->n_lights ? e->ui->light_selector + 1 : 0);
	ui_light_set_id(e);	
	ui_light_update(e);
}
