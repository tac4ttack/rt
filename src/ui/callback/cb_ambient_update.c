/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_ambient_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:33 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:25:31 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	cb_ambient_red_update(GtkSpinButton *spin, gpointer data)
{
	gfloat	value;
	t_env	*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	e->scene->ambient.x = (float)value;
	return (FALSE);
}

gboolean	cb_ambient_green_update(GtkSpinButton *spin, gpointer data)
{
	gfloat	value;
	t_env	*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	e->scene->ambient.y = (float)value;
	return (FALSE);
}

gboolean	cb_ambient_blue_update(GtkSpinButton *spin, gpointer data)
{
	gfloat	value;
	t_env	*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value(spin);
	e->scene->ambient.z = (float)value;
	return (FALSE);
}
