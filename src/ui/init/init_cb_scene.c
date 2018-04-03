/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cb_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:00:36 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:00:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cb_scene(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->scene_resolution_width_spin), \
	"value-changed", G_CALLBACK(cb_res_width_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_resolution_height_spin), \
	"value-changed", G_CALLBACK(cb_res_heigh_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_red_spin), \
	"value-changed", G_CALLBACK(cb_ambient_red_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_green_spin), \
	"value-changed", G_CALLBACK(cb_ambient_green_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_blue_spin), \
	"value-changed", G_CALLBACK(cb_ambient_blue_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_depth_spin), \
	"value-changed", G_CALLBACK(cb_depth_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_supersampling_scale), \
	"value-changed", G_CALLBACK(cb_supersampling_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_none_radio), \
	"toggled", G_CALLBACK(cb_postproc_none), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_bw_radio), \
	"toggled", G_CALLBACK(cb_postproc_bw), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_sepia_radio), \
	"toggled", G_CALLBACK(cb_postproc_sepia), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_invert_check), \
	"toggled", G_CALLBACK(cb_postproc_invert), (gpointer)e);
}
