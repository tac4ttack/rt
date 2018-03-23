#include "rt.h"

static void	cam_remove(t_env *e, int target)
{
	t_cam		*new_array;
	int			i;
	int			j;

	i = 0;
	j = 0;
	new_array = NULL;
	if (!(new_array = malloc(sizeof(t_cam) * (NCAM - 1))))
		s_error("\x1b[1;31mCan't recreate cameras array\x1b[0m", e);
	while (i < (int)NCAM)
	{
		if (i == target)
			i++;
		else
		{
			ft_memcpy(&new_array[j], &e->cameras[i], sizeof(t_cam));
			j++;
			i++;
		}
	}
	free(e->cameras);
	e->cameras = new_array;
}

static void	cam_add(t_env *e)
{
	t_cam		*new_array;
	int			i;

	i = 0;
	new_array = NULL;
	if (!(new_array = malloc(sizeof(t_cam) * (NCAM + 1))))
		s_error("\x1b[1;31mCan't recreate cameras array\x1b[0m", e);
	while (i < (int)NCAM + 1)
	{
			ft_memcpy(&new_array[i], &e->cameras[i], sizeof(t_cam));
			i++;
	}
	new_array[i - 1].pos.x = 0;
	new_array[i - 1].pos.y = 0;
	new_array[i - 1].pos.z = 0;
	new_array[i - 1].dir.x = 0;
	new_array[i - 1].dir.y = 0;
	new_array[i - 1].dir.z = 1;
	new_array[i - 1].fov = 30;
	new_array[i - 1].pitch = 0;
	new_array[i - 1].yaw = 0;
	new_array[i - 1].roll = 0;
	free(e->cameras);
	e->cameras = new_array;
}

void	cb_cam_manage_add(GtkButton *btn, gpointer data)
{
	t_env *e;

	(void)btn;
	e = data;
	cam_add(e);
	gtk_widget_set_sensitive(e->ui->cam_nav_prev_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->cam_nav_next_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->cam_nav_del_btn, TRUE);
	e->scene->n_cams++;
	if (!(cl_replace_buffer(e->cl, sizeof(t_cam) * NCAM, 3)))
		s_error("\x1b[2;31mFailed replacing cam buffer\x1b[0m", e);
	e->scene->active_cam = e->scene->n_cams - 1;
	ui_cam_set_id(e);	
	ui_cam_update(e);
	ft_putendl("cam added");
}

void	cb_cam_manage_del(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	if (e->scene->n_cams == 1)
		ft_putendl("why did u du dis? :(((((");
	else
	{
		cam_remove(e, e->scene->active_cam);
		if (--e->scene->n_cams == 1)
		{
			gtk_widget_set_sensitive(e->ui->cam_nav_prev_btn, FALSE);
			gtk_widget_set_sensitive(e->ui->cam_nav_next_btn, FALSE);
			gtk_widget_set_sensitive(e->ui->cam_nav_del_btn, FALSE);
		}
		if (!(cl_replace_buffer(e->cl, sizeof(t_cam) * NCAM, 3)))
			s_error("\x1b[2;31mFailed replacing cam buffer\x1b[0m", e);
		e->scene->active_cam = 0;
		ui_cam_set_id(e);	
		ui_cam_update(e);
	}
}
