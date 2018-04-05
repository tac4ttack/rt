/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_about_dialog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:29 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:25:20 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_about_btn(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	gtk_dialog_run(GTK_DIALOG(e->ui->about_window));
	gtk_widget_destroy(e->ui->about_window);
}
