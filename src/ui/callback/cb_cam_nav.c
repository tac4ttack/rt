/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_cam_nav.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:41 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/07 16:42:08 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ui_cam_set_id(t_env *e)
{
	char	*cam_id;

	cam_id = ft_strjoin_frs2("CAMERA ", ft_itoa(e->scene->active_cam + 1));
	cam_id = ft_strjoin_frs1(cam_id, " / ");
	cam_id = ft_strjoin_free(cam_id, ft_itoa(e->scene->n_cams));
	gtk_label_set_text(GTK_LABEL(e->ui->cam_list_id_label), (gchar*)cam_id);
	free(cam_id);
}

void		cb_cam_nav_prev(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	if (e->scene->active_cam == 0)
		e->scene->active_cam = e->scene->n_cams - 1;
	else
		e->scene->active_cam--;
	ui_cam_set_id(e);
	ui_cam_update(e);
}

void		cb_cam_nav_next(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	if (e->scene->active_cam == e->scene->n_cams - 1)
		e->scene->active_cam = 0;
	else
		e->scene->active_cam++;
	ui_cam_set_id(e);
	ui_cam_update(e);
}
