/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_ellipsoid_radius.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:58 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:26:56 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_ellipsoid_radius(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_ellipsoid	*ellipsoid;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	ellipsoid = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	ellipsoid->radius = (float)value;
	return (TRUE);
}
