/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_object_sinwave.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:38:07 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 18:04:10 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gtk_object_sinwave(t_env *e)
{
	e->ui->obj_list_sinwave = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_sinwave"));
	e->ui->obj_sinwave_button = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_sinwave_button"));
	e->ui->obj_sinwave_param1_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_sinwave_param1_spin_x"));
	e->ui->obj_sinwave_param1_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_sinwave_param1_spin_y"));
	e->ui->obj_sinwave_param1_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_sinwave_param1_spin_z"));
	e->ui->obj_sinwave_param2_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_sinwave_param2_spin_x"));
	e->ui->obj_sinwave_param2_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_sinwave_param2_spin_y"));
	e->ui->obj_sinwave_param2_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_sinwave_param2_spin_z"));
}
