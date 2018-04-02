/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cb_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:43 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/02 12:10:47 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	init_cb_cam_dir(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_dir_spin_x), \
	"value-changed", G_CALLBACK(cb_cam_dir_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_dir_spin_y), \
	"value-changed", G_CALLBACK(cb_cam_dir_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_dir_spin_z), \
	"value-changed", G_CALLBACK(cb_cam_dir_z), (gpointer)e);
}

void		init_cb_cam(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_pos_spin_x), \
	"value-changed", G_CALLBACK(cb_cam_pos_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_pos_spin_y), \
	"value-changed", G_CALLBACK(cb_cam_pos_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_pos_spin_z), \
	"value-changed", G_CALLBACK(cb_cam_pos_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_fov_spin), \
	"value-changed", G_CALLBACK(cb_cam_fov_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_prev_btn), \
	"clicked", G_CALLBACK(cb_cam_nav_prev), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_next_btn), \
	"clicked", G_CALLBACK(cb_cam_nav_next), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_add_btn), \
	"clicked", G_CALLBACK(cb_cam_manage_add), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_del_btn), \
	"clicked", G_CALLBACK(cb_cam_manage_del), (gpointer)e);
	init_cb_cam_dir(e);
}
