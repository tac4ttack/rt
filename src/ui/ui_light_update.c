#include "rt.h"

void		ui_light_update(t_env *e)
{
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_x, (gdouble)ACTIVELIGHT.pos.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_y, (gdouble)ACTIVELIGHT.pos.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_z, (gdouble)ACTIVELIGHT.pos.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_bright_spin, (gdouble)ACTIVELIGHT.brightness);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_shrink_spin, (gint)ACTIVELIGHT.shrink);
	e->ui->light_color = ui_int_to_gdkrbga((gint)ACTIVELIGHT.color);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(e->ui->light_list_color_button), &e->ui->light_color);
}

