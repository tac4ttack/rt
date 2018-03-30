/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cam_fov_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:36 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:52:28 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	cb_cam_fov_update(GtkSpinButton *spin, gpointer data)
{
	gint	value;
	t_env	*e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	ACTIVECAM.fov = (int)value;
	return (FALSE);
}
