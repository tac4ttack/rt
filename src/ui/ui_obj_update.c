/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui_obj_update.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 20:12:43 by fmessina          #+#    #+#             */
/*   Updated: 2018/03/30 20:13:34 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		ui_obj_get_id(t_env *e, t_object *obj)
{
	char		*obj_label;

	obj_label = ft_strjoin_frs1(ft_itoa(gen_get_ptr_index(e->gen_objects, obj) \
														+ 1), "# ");
	if (obj->type == OBJ_CONE)
		obj_label = ft_strjoin_frs1(obj_label, " CONE");
	else if (obj->type == OBJ_CYLINDER)
		obj_label = ft_strjoin_frs1(obj_label, " CYLINDER");
	else if (obj->type == OBJ_PLANE)
		obj_label = ft_strjoin_frs1(obj_label, " PLANE");
	else if (obj->type == OBJ_SPHERE)
		obj_label = ft_strjoin_frs1(obj_label, " SPHERE");
	else if (obj->type == OBJ_ELLIPSOID)
		obj_label = ft_strjoin_frs1(obj_label, " ELLIPSOID");
	else if (obj->type == OBJ_TORUS)
		obj_label = ft_strjoin_frs1(obj_label, " TORUS");
	gtk_label_set_text(GTK_LABEL(e->ui->obj_list_id_label), obj_label);
	free(obj_label);
}

static	void	ui_obj_set_base(t_env *e, t_object *obj)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_pos_spin_x, \
	(gdouble)obj->pos.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_pos_spin_y, \
	(gdouble)obj->pos.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_pos_spin_z, \
	(gdouble)obj->pos.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_dir_spin_x, \
	(gdouble)obj->dir.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_dir_spin_y, \
	(gdouble)obj->dir.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_dir_spin_z, \
	(gdouble)obj->dir.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_diff_spin_x, \
	(gdouble)obj->diff.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_diff_spin_y, \
	(gdouble)obj->diff.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_diff_spin_z, \
	(gdouble)obj->diff.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_spec_spin_x, \
	(gdouble)obj->spec.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_spec_spin_y, \
	(gdouble)obj->spec.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_spec_spin_z, \
	(gdouble)obj->spec.z);
}

static	void	ui_obj_set_aux(t_env *e, t_object *obj)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_reflex_spin, \
	(gdouble)obj->reflex);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_refrac_spin, \
	(gdouble)obj->refract);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_opacity_spin,\
	(gdouble)obj->opacity);
	e->ui->obj_color = int_to_gdkrbga((gint)obj->color);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(e->ui->obj_list_color_btn), \
	&e->ui->obj_color);
}

static	void	ui_obj_set_custom(t_env *e, t_object *obj)
{
	if (obj->type == OBJ_CONE)
		ui_obj_set_cone(e, (t_cone*)obj);
	if (obj->type == OBJ_CYLINDER)
		ui_obj_set_cylinder(e, (t_cylinder*)obj);
	else if (obj->type == OBJ_PLANE)
		ui_obj_set_plane(e, (t_plane*)obj);
	else if (obj->type == OBJ_SPHERE)
		ui_obj_set_sphere(e, (t_sphere*)obj);
	else if (obj->type == OBJ_ELLIPSOID)
		ui_obj_set_ellipsoid(e, (t_ellipsoid*)obj);
	else if (obj->type == OBJ_TORUS)
		ui_obj_set_torus(e, (t_torus*)obj);
}

void			ui_obj_update(t_env *e, t_object *obj)
{
	if (e->target > -1)
	{
		gtk_widget_show(e->ui->obj_list_box);
		gtk_widget_show(e->ui->obj_nav_prev_btn);
		gtk_widget_show(e->ui->obj_nav_next_btn);
		gtk_widget_show(e->ui->obj_nav_del_btn);
		gtk_combo_box_set_active((GtkComboBox*)e->ui->obj_nav_jump_combo,\
		gen_get_ptr_index(e->gen_objects, obj));
		ui_obj_get_id(e, obj);
		ui_obj_set_base(e, obj);
		ui_obj_set_aux(e, obj);
		ui_obj_set_custom(e, obj);
	}
	else
	{
		gtk_widget_hide(e->ui->obj_list_box);
		gtk_widget_hide(e->ui->obj_nav_prev_btn);
		gtk_widget_hide(e->ui->obj_nav_next_btn);
		gtk_widget_hide(e->ui->obj_nav_del_btn);
	}
}
