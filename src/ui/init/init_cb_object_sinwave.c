/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cb_object_sinwave.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:32:55 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 16:20:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cb_object_sinwave(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->obj_sinwave_button), \
	"clicked", G_CALLBACK(cb_obj_sinwave_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_sinwave_param1_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_sinwave_param1_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_sinwave_param1_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_sinwave_param1_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_sinwave_param1_spin_z), \
	"value-changed", G_CALLBACK(cb_obj_sinwave_param1_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_sinwave_param2_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_sinwave_param2_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_sinwave_param2_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_sinwave_param2_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_sinwave_param2_spin_z), \
	"value-changed", G_CALLBACK(cb_obj_sinwave_param2_z), (gpointer)e);
}
