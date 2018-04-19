/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_texture_diff_chooser.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:47:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/19 15:53:03 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cb_obj_texture_diff_chooser(GtkComboBox *box, gpointer data)
{
	t_env		*e;
	gint		index;
	t_object	*obj;

	e = data;
	(void)box;
	index = gtk_combo_box_get_active(box);
	obj = e->gen_objects->mem + e->target;
	obj->diff_map_id = index - 1;
}
