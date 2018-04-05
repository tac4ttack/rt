/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_light_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:07 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:26:08 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_light_pos_x(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	A_LIG.pos.x = (float)value;
	return (TRUE);
}

gboolean		cb_light_pos_y(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	A_LIG.pos.y = (float)value;
	return (TRUE);
}

gboolean		cb_light_pos_z(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	A_LIG.pos.z = (float)value;
	return (TRUE);
}
