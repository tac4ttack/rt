/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_sphere_radius.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:49 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:32:29 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_sphere_radius(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_sphere	*sphere;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	sphere = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	sphere->radius = (float)value;
	return (TRUE);
}
