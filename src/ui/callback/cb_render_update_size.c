/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_render_update_size.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:41 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/20 16:29:46 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_render_update_size(GtkContainer *box, gpointer data)
{
	t_env	*e;
	int		zone[2];

	e = data;
	(void)box;
	zone[0] = gtk_widget_get_allocated_width(e->ui->render);
	zone[1] = gtk_widget_get_allocated_height(e->ui->render);
	gtk_widget_queue_draw_area(e->ui->render, 0, 0, zone[0], zone[1]);
}
