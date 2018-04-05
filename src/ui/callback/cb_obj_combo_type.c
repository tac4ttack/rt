/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_combo_type.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:10 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:30:08 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	cb_obj_combo_type(GtkComboBox *box, gpointer data)
{
	t_env		*e;
	gint		index;

	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	index = gtk_combo_box_get_active(box);
	if (index == -1)
		gtk_widget_set_sensitive(e->ui->obj_nav_add_btn, FALSE);
	else if (index >= 0)
		gtk_widget_set_sensitive(e->ui->obj_nav_add_btn, TRUE);
}
