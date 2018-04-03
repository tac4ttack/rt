/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_obj_texture_diff_chooser.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:47:45 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 19:22:23 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_obj_texture_diff_chooser(GtkComboBox *box, gpointer data)
{
	t_env	*e;
//	gint	index;
	//void	*obj;

	e = data;
	(void)box;
	ft_putendl("TOTO CACA!");
	// index = gtk_combo_box_get_active(box);
	// if (index > -1)
	// {
	// 	obj = gen_get_index_ptr(e->gen_objects, index);
	// 	e->target = obj - e->gen_objects->mem;
	// 	ui_obj_update(e, obj);
	// }
}
