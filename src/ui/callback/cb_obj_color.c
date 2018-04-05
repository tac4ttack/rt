/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:09 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:45:36 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_color(GtkColorButton *button, gpointer data)
{
	t_env		*e;
	GdkRGBA		new_color;
	t_object	*obj;

	e = data;
	obj = e->gen_objects->mem + e->target;
	new_color.alpha = 1;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(button), &new_color);
	obj->color = gdkrgba_to_int(new_color);
	e->ui->obj_color = new_color;
}
