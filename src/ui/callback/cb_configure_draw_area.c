/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_configure_draw_area.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:48 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/20 16:28:28 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		clear_surface(t_env *e)
{
	cairo_t	*cr;

	cr = cairo_create(e->ui->surface);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_paint(cr);
	cairo_destroy(cr);
}

gboolean	cb_configure_draw_area(GtkWidget *widget, \
									GdkEventConfigure *event, \
									gpointer data)
{
	t_env	*e;

	e = data;
	e->ui->render_pos[0] = event->x;
	e->ui->render_pos[1] = event->y + 45;
	e->ui->render_pos[2] = event->width;
	e->ui->render_pos[3] = event->height;
	if (e->ui->surface)
		cairo_surface_destroy(e->ui->surface);
	e->ui->surface = gdk_window_create_similar_surface(\
						gtk_widget_get_window(widget), \
						CAIRO_CONTENT_COLOR, \
						gtk_widget_get_allocated_width(widget), \
						gtk_widget_get_allocated_height(widget));
	clear_surface(e);
	return (TRUE);
}
