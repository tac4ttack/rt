#include "rt.h"

gboolean	gtk_main_loop(gpointer data)
{
	t_env	*e;
	char	*fps;

	e = (t_env *)data;
	fps = NULL;
	while (e)
	{
		if (e->ui->redraw == 1)
		{
			gtk_widget_set_sensitive(e->ui->tool_play_btn, FALSE);
			gtk_widget_set_sensitive(e->ui->tool_stop_btn, TRUE);
			update_fps(&e->fps);
			fps = ft_strjoin_frs1(ft_itoa(e->fps.ret_fps), " ips");
			gtk_label_set_text(GTK_LABEL(e->ui->tool_fps_label), (gchar*)fps);
			opencl_draw(e);
			free(fps);
			gtk_widget_queue_draw_area(e->ui->main_window, 0, 40, e->scene->win_w + 50 , e->scene->win_h + 50);
		}
		else if (e->ui->redraw == 0)
		{
			gtk_widget_set_sensitive(e->ui->tool_play_btn, TRUE);
			gtk_widget_set_sensitive(e->ui->tool_stop_btn, FALSE);
			gtk_label_set_text(GTK_LABEL(e->ui->tool_fps_label), "Realtime rendering paused");
		}
		gtk_render_events(e);
		while (gtk_events_pending())
		{
			if (gtk_main_iteration())
				return (FALSE);
		}
	}
	return (0);
}


/*gboolean	gtk_main_loop(gpointer data)
{
	t_env	*e;
	char	*fps;

	e = (t_env *)data;
	fps = NULL;
	if (e)
	{
		while (e->ui->redraw > 0)
		{
			ft_putendl("gtkmainloop with redraw");
			update_fps(&e->fps);
			fps = ft_strjoin_frs1(ft_itoa(e->fps.ret_fps), " ips");
			gtk_label_set_text(GTK_LABEL(e->ui->tool_fps_label), (gchar*)fps);
			if (gtk_widget_get_sensitive(e->ui->tool_play_btn) == TRUE)
				gtk_widget_set_sensitive(e->ui->tool_play_btn, FALSE);
			if (gtk_widget_get_sensitive(e->ui->tool_stop_btn) == FALSE)
				gtk_widget_set_sensitive(e->ui->tool_play_btn, TRUE);
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
		while (e->ui->redraw == 0)
		{
			ft_putendl("gtkmainloop no redraw");
			gtk_label_set_text(GTK_LABEL(e->ui->tool_fps_label), "Realtime rendering paused");
			if (gtk_widget_get_sensitive(e->ui->tool_play_btn) == FALSE)
				gtk_widget_set_sensitive(e->ui->tool_play_btn, TRUE);
			if (gtk_widget_get_sensitive(e->ui->tool_stop_btn) == TRUE)
				gtk_widget_set_sensitive(e->ui->tool_play_btn, FALSE);
			while (gtk_events_pending())
			{
				if (gtk_main_iteration())
					return (FALSE);
			}
		}
	}
	return (0);
}
*/
