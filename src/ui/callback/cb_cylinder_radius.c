/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cylinder_radius.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:50 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:27:12 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_cylinder_radius(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_cylinder	*cylinder;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	cylinder = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	cylinder->radius = (float)value;
	return (TRUE);
}
