/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj_update_effects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:36:31 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/04 11:22:39 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_obj_update_checkboard(t_env *e, t_object *obj)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_checkboard_width_spin,\
								(gdouble)obj->check_size.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_checkboard_height_spin,\
								(gdouble)obj->check_size.y);
}

void	ui_obj_update_diff_map(t_env *e, t_object *obj)
{
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_texture_diff_offset_spin_x, \
						(gdouble)obj->diff_offset.x);
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_texture_diff_offset_spin_y, \
						(gdouble)obj->diff_offset.y);
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_texture_diff_ratio_spin_x, \
						(gdouble)obj->diff_ratio.x);
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_texture_diff_ratio_spin_y, \
						(gdouble)obj->diff_ratio.y);
//	gtk_combo_box_set_active((GtkComboBox*)e->ui->obj_texture_diff_chooser, \
//	gen_get_ptr_index(e->gen_objects, obj));	//WIP
}

void	ui_obj_update_limit(t_env *e, t_object *obj)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_limit_dir_spin_x, \
								(gdouble)obj->limit_dir.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_limit_dir_spin_y, \
								(gdouble)obj->limit_dir.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_limit_dir_spin_z, \
								(gdouble)obj->limit_dir.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_limit_pos_spin_x, \
								(gdouble)obj->limit_pos.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_limit_pos_spin_y, \
								(gdouble)obj->limit_pos.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_limit_pos_spin_z, \
								(gdouble)obj->limit_pos.z);
}

void	ui_obj_update_sinwave(t_env *e, t_object *obj)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_sinwave_param1_spin_x,\
								(gdouble)obj->waves_p1.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_sinwave_param1_spin_y,\
								(gdouble)obj->waves_p1.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_sinwave_param1_spin_z,\
								(gdouble)obj->waves_p1.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_sinwave_param2_spin_x,\
								(gdouble)obj->waves_p2.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_sinwave_param2_spin_y,\
								(gdouble)obj->waves_p2.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_sinwave_param2_spin_z,\
								(gdouble)obj->waves_p2.z);
}

