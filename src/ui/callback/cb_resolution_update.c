/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_resolution_update.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:48 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/20 11:58:49 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ui_update_resolution(t_env *e, int width, int height)
{
	WIDTH = width;
	HEIGHT = height;
	free(e->pixel_data);
	if (!(e->pixel_data = ft_memalloc(sizeof(int) * WIDTH * HEIGHT)))
		s_error("\x1b[1;31mCan't initialize new pixel buffer\x1b[0m", e);
	if (!(e->cuda->update_buffer(e->cuda, WIDTH * HEIGHT * 4, 0)))
		s_error("\x1b[2;31mFailed replacing Cuda pixel buffer\x1b[0m", e);
	gtk_widget_set_size_request(e->ui->render, WIDTH, HEIGHT);
	g_object_unref(e->ui->pixbuf);
	e->ui->pixbuf = gdk_pixbuf_new_from_data((const guchar *)e->pixel_data, \
					GDK_COLORSPACE_RGB, 1, 8, WIDTH, \
					HEIGHT, WIDTH * 4, NULL, NULL);
	clear_surface(e);
}

gboolean	cb_res_width_update(GtkSpinButton *spin, gpointer data)
{
	gint	value;
	t_env	*e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	ui_update_resolution(e, value, HEIGHT);
	return (TRUE);
}

gboolean	cb_res_heigh_update(GtkSpinButton *spin, gpointer data)
{
	gint	value;
	t_env	*e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	ui_update_resolution(e, WIDTH, value);
	return (TRUE);
}
