/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_object_limit.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:31:31 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 14:36:38 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gtk_object_limit(t_env *e)
{
	e->ui->obj_limit_button = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_limit_button"));
	e->ui->obj_limit_dir_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_limit_dir_spin_x"));
	e->ui->obj_limit_dir_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_limit_dir_spin_y"));
	e->ui->obj_limit_dir_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_limit_dir_spin_z"));
	e->ui->obj_limit_pos_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_limit_pos_spin_x"));
	e->ui->obj_limit_pos_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_limit_pos_spin_y"));
	e->ui->obj_limit_pos_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_limit_pos_spin_z"));
}