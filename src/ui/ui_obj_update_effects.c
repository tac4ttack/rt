/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj_update_effects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/03 18:36:31 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/12 12:10:49 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	ui_obj_update_cut(t_env *e, t_object *obj)
{
	ui_obj_update_cut_norm(e, obj);
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_cut_x_min_spin, \
						(gdouble)obj->cut_min.x);
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_cut_x_max_spin, \
						(gdouble)obj->cut_max.x);
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_cut_y_min_spin, \
						(gdouble)obj->cut_min.y);
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_cut_y_max_spin, \
						(gdouble)obj->cut_max.y);
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_cut_z_min_spin, \
						(gdouble)obj->cut_min.z);
	gtk_spin_button_set_value(\
						(GtkSpinButton*)e->ui->obj_cut_z_max_spin, \
						(gdouble)obj->cut_max.z);
}

void	ui_obj_update_checkboard(t_env *e, t_object *obj)
{
	if (obj->flags & OBJ_FLAG_CHECKERED)
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_checkboard_button), TRUE);
		if (!(obj->flags & OBJ_FLAG_CHECKERED))
			obj->flags |= OBJ_FLAG_CHECKERED;
	}
	else
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_checkboard_button), FALSE);
		if (obj->flags & OBJ_FLAG_CHECKERED)
			obj->flags ^= OBJ_FLAG_CHECKERED;
	}
	gtk_spin_button_set_value(\
		(GtkSpinButton*)e->ui->obj_checkboard_width_spin,\
							(gdouble)obj->check_size.x);
	gtk_spin_button_set_value(\
		(GtkSpinButton*)e->ui->obj_checkboard_height_spin,\
							(gdouble)obj->check_size.y);
}

void	ui_obj_update_diff_map(t_env *e, t_object *obj)
{
	if (obj->flags & OBJ_FLAG_DIFF_MAP)
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_texture_diff_button), TRUE);
		if (!(obj->flags & OBJ_FLAG_DIFF_MAP))
			obj->flags |= OBJ_FLAG_DIFF_MAP;
	}
	else
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_texture_diff_button),\
			FALSE);
		if (obj->flags & OBJ_FLAG_DIFF_MAP)
			obj->flags ^= OBJ_FLAG_DIFF_MAP;
	}
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
}

void	ui_obj_update_limit(t_env *e, t_object *obj)
{
	ui_obj_update_limit_norm(e, obj);
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
	if (obj->flags & OBJ_FLAG_WAVES)
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_sinwave_button), TRUE);
		if (!(obj->flags & OBJ_FLAG_WAVES))
			obj->flags |= OBJ_FLAG_WAVES;
	}
	else
	{
		gtk_toggle_button_set_active(GTB(e->ui->obj_sinwave_button), FALSE);
		if (obj->flags & OBJ_FLAG_WAVES)
			obj->flags ^= OBJ_FLAG_WAVES;
	}
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
