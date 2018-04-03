/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gtk_object_checkboard.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 14:39:58 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 14:40:49 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_gtk_object_checkboard(t_env *e)
{
	e->ui->obj_list_checkboard = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_list_checkboard"));
	e->ui->obj_checkboard_button = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_checkboard_button"));
	e->ui->obj_checkboard_width_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_checkboard_width_spin"));
	e->ui->obj_checkboard_height_spin = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "obj_checkboard_height_spin"));
}
