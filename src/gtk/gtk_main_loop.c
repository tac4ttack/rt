#include "rt.h"

gboolean		gtk_main_loop(gpointer ptr)
{
	t_env *e;
	char *fps;

	e = (t_env *)ptr;
	fps = NULL;
	if (e)
	{
		while (e->ui->redraw > 0)
		{
//			ft_putendl("im in gtk main loop");
	
			update_fps(&e->fps);
			fps = ft_itoa(e->fps.ret_fps);
			fps = ft_strjoin_frs2("RT - ", fps);
			fps = ft_strjoin_frs1(fps, " ips");
		//	printf("%s\n", fps);
		//	ft_putendl(fps); // Controle semble ok
			gtk_window_set_title(GTK_WINDOW(e->ui->main_window), fps);

			opencl_draw(e);

			free(fps);

		//	gtk_widget_queue_draw_area(e->ui->main_window, 0, 40, 2000, 1200);
			gtk_widget_queue_draw_area(e->ui->main_window, 0, 40, e->win_w, e->win_h);
			while (gtk_events_pending())
			{
				if (gtk_main_iteration())
					return (FALSE);
			}
		}
	}
	return (0);
}
