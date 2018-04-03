/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cb_object_limit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:32:55 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 15:39:47 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cb_object_limit(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->obj_limit_button), \
	"clicked", G_CALLBACK(cb_obj_limit_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_limit_dir_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_limit_dir_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_limit_dir_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_limit_dir_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_limit_dir_spin_z), \
	"value-changed", G_CALLBACK(cb_obj_limit_dir_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_limit_pos_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_limit_pos_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_limit_pos_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_limit_pos_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_limit_pos_spin_z), \
	"value-changed", G_CALLBACK(cb_obj_limit_pos_z), (gpointer)e);
}
