/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cylinder_radius.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:50 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:48:58 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_cylinder_radius(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_cylinder	*cylinder;

	e = data;
	cylinder = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	cylinder->radius = (float)value;
	return (TRUE);
}
