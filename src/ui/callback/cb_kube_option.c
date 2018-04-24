/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_kuber_option.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:50 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/15 14:48:53 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean		cb_kube_option(GtkSpinButton *spin, gpointer data)
{
	gdouble		value;
	t_env		*e;
	t_kube		*kube;

	e = data;
	kube = e->gen_objects->mem + e->target;
	value = gtk_spin_button_get_value(spin);
	kube->option = value;
	return (TRUE);
}
