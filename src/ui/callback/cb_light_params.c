/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_light_params.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:05 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:26:17 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_light_shrink(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value_as_int(spin);
	A_LIG.shrink = value;
	return (TRUE);
}

gboolean		cb_light_brightness(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	A_LIG.brightness = (float)value;
	return (TRUE);
}

void			cb_light_color(GtkColorButton *button, gpointer data)
{
	t_env		*e;
	GdkRGBA		new_color;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	new_color.alpha = 1;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(button), &new_color);
	A_LIG.color = gdkrgba_to_int(new_color);
	e->ui->light_color = new_color;
}
