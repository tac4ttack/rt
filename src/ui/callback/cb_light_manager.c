#include "rt.h"

// static void	light_remove(t_env *e, int target)
// {
	// t_cam		*new_array;
	// int			i;
	// int			j;

	// i = 0;
	// j = 0;
	// new_array = NULL;
	// if (!(new_array = malloc(sizeof(t_light) * (NLIG - 1))))
	// 	s_error("\x1b[1;31mCan't recreate lightss array\x1b[0m", e);
	// while (i < (int)NLIG)
	// {
	// 	if (i == target)
	// 		i++;
	// 	else
	// 	{
	// 		ft_memcpy(&new_array[j], &e->light[i], sizeof(t_cam));
	// 		j++;
	// 		i++;
	// 	}
	// }
	// free(e->cameras);
	// e->cameras = new_array;
//}

void	cb_light_manage_del(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;
	// if (	e->gen_lights->unit_size == 1) // TO REMOVE OR HANDLE THE ERROR
	// 	ft_putendl("why did u du dis? :(((((");
	// else
	// {
	// //	light_remove(e, e->ui->light_selector);
	// 	if (--e->gen_lights->unit_size == 1)
	// 	{
	// 		gtk_widget_set_sensitive(e->ui->light_nav_prev_btn, FALSE);
	// 		gtk_widget_set_sensitive(e->ui->light_nav_next_btn, FALSE);
	// 		gtk_widget_set_sensitive(e->ui->light_nav_del_btn, FALSE);
	// 	}
	// 	if (!(cl_replace_buffer(e->cl, sizeof(t_light) * NLIG, 4)))
	// 		s_error("\x1b[2;31mFailed replacing light buffer\x1b[0m", e);
	// 	e->ui->light_selector = NLIG - 1;
	// 	ui_light_set_id(e);	
	// 	ui_light_update(e);
	// }
	
}

void	cb_light_manage_add(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;

	gtk_widget_set_sensitive(e->ui->light_nav_prev_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->light_nav_next_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->light_nav_del_btn, TRUE);
}
