/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cb_obj_cut.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ntoniolo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 19:09:38 by ntoniolo          #+#    #+#             */
/*   Updated: 2018/04/14 19:09:39 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cb_obj_cut(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->obj_cut_x_min_spin), \
	"value-changed", G_CALLBACK(cb_obj_cut_x_min), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_cut_x_max_spin), \
	"value-changed", G_CALLBACK(cb_obj_cut_x_max), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_cut_y_min_spin), \
	"value-changed", G_CALLBACK(cb_obj_cut_y_min), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_cut_y_max_spin), \
	"value-changed", G_CALLBACK(cb_obj_cut_y_max), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_cut_z_min_spin), \
	"value-changed", G_CALLBACK(cb_obj_cut_z_min), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_cut_z_max_spin), \
	"value-changed", G_CALLBACK(cb_obj_cut_z_max), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_cut_check), \
	"toggled", G_CALLBACK(cb_obj_cut_check), (gpointer)e);
}
