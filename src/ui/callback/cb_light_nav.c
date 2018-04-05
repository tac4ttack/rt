/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_light_nav.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:03 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/05 23:26:34 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ui_light_set_id(t_env *e)
{
	char	*light_id;

	light_id = ft_strjoin_frs2("LIGHT ", ft_itoa(e->ui->light_selector + 1));
	light_id = ft_strjoin_frs1(light_id, " / ");
	light_id = ft_strjoin_free(light_id, ft_itoa(e->gen_lights->length));
	gtk_label_set_text(GTK_LABEL(e->ui->light_list_id_label), (gchar*)light_id);
	free(light_id);
}

void		cb_light_nav_prev(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	e->ui->light_selector = ((int)e->ui->light_selector - 1 \
	< 0 ? e->gen_lights->length - 1 : e->ui->light_selector - 1);
	ui_light_set_id(e);
	ui_light_update(e);
}

void		cb_light_nav_next(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	e->ui->light_selector = (e->ui->light_selector + 1 \
	< e->gen_lights->length ? e->ui->light_selector + 1 : 0);
	ui_light_set_id(e);
	ui_light_update(e);
}
