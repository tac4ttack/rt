/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_obj_cut.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 19:10:03 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 19:10:06 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gtk_obj_cut(t_env *e)
{
	e->ui->obj_list_cut = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_cut"));
	e->ui->obj_cut_x_min_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_x_min_spin"));
	e->ui->obj_cut_x_max_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_x_max_spin"));
	e->ui->obj_cut_y_min_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_y_min_spin"));
	e->ui->obj_cut_y_max_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_y_max_spin"));
	e->ui->obj_cut_z_min_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_z_min_spin"));
	e->ui->obj_cut_z_max_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_z_max_spin"));
	e->ui->obj_cut_check = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_cut_check"));
}
