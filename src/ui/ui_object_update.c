#include "rt.h"

void			ui_obj_set_id(t_env *e, t_object *obj)
{
	char		*object_id;

	if (e->target > -1)
	{
		gtk_widget_show(e->ui->obj_list_box);
		object_id = ft_strjoin_frs1(ft_itoa(obj->id - NCAM), "# ");
		if (obj->type == OBJ_CYLINDER)
			object_id = ft_strjoin_frs1(object_id, " CYLINDER");
		else if (obj->type == OBJ_PLANE)
			object_id = ft_strjoin_frs1(object_id, " PLANE");
		else if (obj->type == OBJ_SPHERE)
			object_id = ft_strjoin_frs1(object_id, " SPHERE");
		else if (obj->type == OBJ_ELLIPSOID)
			object_id = ft_strjoin_frs1(object_id, " ELLIPSOID");
		else if (obj->type == OBJ_PARABOLOID)
			object_id = ft_strjoin_frs1(object_id, " PARABOLOID");
		else if (obj->type == OBJ_TORUS)
			object_id = ft_strjoin_frs1(object_id, " TORUS");
		gtk_label_set_text(GTK_LABEL(e->ui->obj_list_id_label), object_id);
		free(object_id);
	}
	else
		gtk_widget_hide(e->ui->obj_list_box);
}

void		ui_obj_update(t_env *e, t_object *obj)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_pos_spin_x, (gdouble)obj->pos.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_pos_spin_y, (gdouble)obj->pos.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_pos_spin_z, (gdouble)obj->pos.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_dir_spin_x, (gdouble)obj->dir.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_dir_spin_y, (gdouble)obj->dir.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_dir_spin_z, (gdouble)obj->dir.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_diff_spin_x, (gdouble)obj->diff.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_diff_spin_y, (gdouble)obj->diff.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_diff_spin_z, (gdouble)obj->diff.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_spec_spin_x, (gdouble)obj->spec.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_spec_spin_y, (gdouble)obj->spec.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_spec_spin_z, (gdouble)obj->spec.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_reflex_spin, (gdouble)obj->reflex);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_refrac_spin, (gdouble)obj->refract);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->obj_list_opacity_spin, (gdouble)obj->opacity);
	e->ui->obj_color = ui_int_to_gdkrbga((gint)obj->color);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(e->ui->obj_list_color_button), &e->ui->obj_color);
	// puis appel a la fonction specialisee
}

