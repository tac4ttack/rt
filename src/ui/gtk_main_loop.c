#include "rt.h"

gboolean	gtk_main_loop(gpointer data)
{
	t_env	*e;
	char	*fps;

	e = (t_env *)data;
	fps = NULL;
	if (e)
	{
		while (e->ui->redraw > 0)
		{
			update_fps(&e->fps);
			fps = ft_strjoin("RT - ", e->scene_target);
			fps = ft_strjoin_frs1(fps, " - ");
			fps = ft_strjoin_free(fps, ft_itoa(e->fps.ret_fps));
		//	gtk_window_set_title(GTK_WINDOW(e->ui->main_window), fps);
			opencl_draw(e);
			free(fps);
			gtk_render_events(e);
			gtk_widget_queue_draw_area(e->ui->main_window, 0, 40, e->scene->win_w + 50 , e->scene->win_h + 50);
			while (gtk_events_pending())
			{
				if (gtk_main_iteration())
					return (FALSE);
			}
		}
	}
	return (0);
}
