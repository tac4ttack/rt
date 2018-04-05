/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:15 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:43:52 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_obj_jump_combo(GtkComboBox *box, gpointer data)
{
	t_env	*e;
	gint	index;
	void	*obj;

	e = data;
	index = gtk_combo_box_get_active(box);
	if (index > -1)
	{
		obj = gen_get_index_ptr(e->gen_objects, index);
		e->target = obj - e->gen_objects->mem;
		ui_obj_update(e, obj);
	}
}
