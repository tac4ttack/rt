/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cb_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:41 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:00:42 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cb_light(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->light_list_pos_spin_x), \
	"value-changed", G_CALLBACK(cb_light_pos_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_list_pos_spin_y), \
	"value-changed", G_CALLBACK(cb_light_pos_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_list_pos_spin_z), \
	"value-changed", G_CALLBACK(cb_light_pos_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_list_bright_spin), \
	"value-changed", G_CALLBACK(cb_light_brightness), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_list_shrink_spin), \
	"value-changed", G_CALLBACK(cb_light_shrink), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_list_color_btn), \
	"color-set", G_CALLBACK(cb_light_color), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_prev_btn), \
	"clicked", G_CALLBACK(cb_light_nav_prev), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_next_btn), \
	"clicked", G_CALLBACK(cb_light_nav_next), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_add_btn), \
	"clicked", G_CALLBACK(cb_light_manage_add), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_del_btn), \
	"clicked", G_CALLBACK(cb_light_manage_del), (gpointer)e);
}
