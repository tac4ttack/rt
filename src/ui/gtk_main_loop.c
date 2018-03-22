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
			fps = ft_strjoin_frs1(ft_itoa(e->fps.ret_fps), " fps");
			gtk_label_set_text(GTK_LABEL(e->ui->tool_fps_label), (gchar*)fps);
			opencl_draw(e);
			free(fps);
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
				return (TRUE);
		}
	}
	return (0);
}
