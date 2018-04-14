/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cb_light_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:17:02 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/14 00:36:27 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cb_light_manage_add(GtkButton *btn, gpointer data)
{
	t_env	*e;
	t_light new_light;

	(void)btn;
	e = data;
	new_light.size = sizeof(t_light);
	new_light.pos.x = 0;
	new_light.pos.y = 0;
	new_light.pos.z = 0;
	new_light.dir.x = 0;
	new_light.dir.y = 0;
	new_light.dir.z = 0;
	new_light.type = 0;
	new_light.brightness = 0.21;
	new_light.shrink = 21;
	new_light.color = 0x00ffffff;
	e->gen_lights->add(e->gen_lights, (void *)&new_light);
	gtk_widget_set_sensitive(e->ui->light_nav_prev_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->light_nav_next_btn, TRUE);
	gtk_widget_set_sensitive(e->ui->light_nav_del_btn, TRUE);
	e->ui->light_selector = e->gen_lights->length - 1;
//	if (e->cl)
//	{
//		if (!(cl_replace_buffer(e->cl, e->gen_lights->mem_size, 4)))
//			s_error("\x1b[2;31mFailed replacing cam buffer\x1b[0m", e);
//	}
//	else
//	{
		if (!(e->cuda->update_buffer(e->cuda, e->gen_lights->mem_size, 2)))
			s_error("\x1b[2;31mFailed replacing cam buffer\x1b[0m", e);
//	}
	ui_light_set_id(e);
	ui_light_update(e);
}

void		cb_light_manage_del(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	e->gen_lights->remove_index(e->gen_lights, e->ui->light_selector);
	if (e->gen_lights->length == 1)
	{
		gtk_widget_set_sensitive(e->ui->light_nav_prev_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->light_nav_next_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->light_nav_del_btn, FALSE);
	}
//	if (e->cl)
//	{
//		if (!(cl_replace_buffer(e->cl, e->gen_lights->mem_size, 4)))
//			s_error("\x1b[2;31mFailed replacing cam buffer\x1b[0m", e);
//	}
//	else
//	{
		if (!(e->cuda->update_buffer(e->cuda, e->gen_lights->mem_size, 2)))
			s_error("\x1b[2;31mFailed replacing cam buffer\x1b[0m", e);
//	}
	if (e->gen_lights->length == 1)
		e->ui->light_selector = 0;
	else if (e->ui->light_selector == 0)
		e->ui->light_selector = 0;
	else
		e->ui->light_selector -= 1;
	ui_light_set_id(e);
	ui_light_update(e);
}
