/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cam_fov_update.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:36 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:28:06 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

gboolean	cb_cam_fov_update(GtkSpinButton *spin, gpointer data)
{
	gint	value;
	t_env	*e;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	value = gtk_spin_button_get_value_as_int(spin);
	A_CAM.fov = (int)value;
	return (FALSE);
}
