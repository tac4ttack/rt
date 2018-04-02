/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_render_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:39 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:28:26 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	cb_render_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	t_env	*e;

	(void)widget;
	e = data;
	gdk_cairo_set_source_pixbuf(cr, e->ui->pixbuf, 0, 0);
	cairo_paint(cr);
	return (FALSE);
}
