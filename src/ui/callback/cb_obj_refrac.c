/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_refrac.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:35 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:28:31 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_obj_refrac(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_object	*obj;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	obj = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	if (value > 0 && value < 1)
		value = 1;
	gtk_spin_button_set_value(spin, value);
	obj->refract = (float)value;
	return (TRUE);
}
