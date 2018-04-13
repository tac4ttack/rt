/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtk_main_loop.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:01:06 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/13 17:42:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			update_fps(&e->fps);
			fps = ft_strjoin_frs1(ft_itoa(e->fps.ret_fps), " fps");
			gtk_label_set_text(GTK_LABEL(e->ui->tool_fps_label), (gchar*)fps);
			draw(e);
			free(fps);
		}
		else if (e->ui->redraw == 0)
			gtk_label_set_text(GTK_LABEL(e->ui->tool_fps_label), "PAUSED");
		gtk_render_events(e);
		while (gtk_events_pending())
		{
			if (gtk_main_iteration())
				return (TRUE);
		}
	}
	return (0);
}
