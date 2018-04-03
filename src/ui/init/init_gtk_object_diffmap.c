/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_object_diffmap.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:41:05 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 14:42:33 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gtk_object_diffmap(t_env *e)
{
	e->ui->obj_list_texture_diff = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_texture_diff"));
	e->ui->obj_texture_diff_button = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_texture_diff_button"));
	e->ui->obj_texture_diff_offset_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_texture_diff_offset_spin_x"));
	e->ui->obj_texture_diff_offset_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_texture_diff_offset_spin_y"));
	e->ui->obj_texture_diff_ratio_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_texture_diff_ratio_spin"));
	e->ui->obj_texture_diff_chooser = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_texture_diff_chooser"));
}
