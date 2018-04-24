/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_about_dialog.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:16:29 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/06 17:46:07 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_about_btn(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	gtk_dialog_run(GTK_DIALOG(e->ui->about_window));
	gtk_widget_hide(e->ui->about_window);
}
