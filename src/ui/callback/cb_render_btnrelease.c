/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_render_btnrelease.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/13 19:36:50 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	cb_render_btnrelease(GtkWidget *widget, GdkEvent *ev, gpointer data)
{
	t_env	*e;

	(void)ev;
	e = data;
	if (gtk_widget_is_focus(widget) == FALSE)
		gtk_widget_grab_focus(widget);
	ui_obj_update(e, e->gen_objects->mem + e->target);
	return (TRUE);
}
