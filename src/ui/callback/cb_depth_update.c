/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_depth_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:54 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:27:09 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	cb_depth_update(GtkSpinButton *spin, gpointer data)
{
	gint	value;
	t_env	*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value_as_int(spin);
	e->scene->depth = (int)value;
	return (FALSE);
}
