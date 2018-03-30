/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_render_btnpress.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:39:31 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	cb_render_btnpress(GtkWidget *widget, GdkEvent *ev, gpointer data)
{
	t_env	*e;

	(void)widget;
	(void)ev;
	e = data;
	e->scene->flag |= OPTION_RUN;
	e->scene->mou_x = (int)ev->button.x;
	e->scene->mou_y = (int)ev->button.y;
	if (gtk_widget_is_focus(widget) == FALSE)
		gtk_widget_grab_focus(widget);
	ui_obj_update(e, e->gen_objects->mem + e->target);
	return (TRUE);
}
