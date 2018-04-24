/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cb_object_checkboard.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 15:32:55 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 15:48:06 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	init_cb_object_checkboard(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->obj_checkboard_button), \
	"clicked", G_CALLBACK(cb_obj_checkboard_button), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_checkboard_width_spin), \
	"value-changed", G_CALLBACK(cb_obj_checkboard_width), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_checkboard_height_spin), \
	"value-changed", G_CALLBACK(cb_obj_checkboard_height), (gpointer)e);
}
