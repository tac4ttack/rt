/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cb_object_diffmap.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:32:55 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 19:27:42 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cb_object_diffmap(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->obj_texture_diff_button), \
	"clicked", G_CALLBACK(cb_obj_texture_diff_button), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_texture_diff_offset_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_texture_diff_offset_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_texture_diff_offset_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_texture_diff_offset_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_texture_diff_ratio_spin_x), \
	"value-changed", G_CALLBACK(cb_obj_texture_diff_ratio_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_texture_diff_ratio_spin_y), \
	"value-changed", G_CALLBACK(cb_obj_texture_diff_ratio_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_texture_diff_chooser), \
	"changed", G_CALLBACK(cb_obj_texture_diff_chooser), (gpointer)e);
}
