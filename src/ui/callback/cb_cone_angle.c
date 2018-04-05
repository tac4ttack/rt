/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cone_angle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:46 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:49:52 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_cone_angle(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_cone		*cone;

	e = data;
	cone = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	cone->angle = (float)value;
	return (TRUE);
}
