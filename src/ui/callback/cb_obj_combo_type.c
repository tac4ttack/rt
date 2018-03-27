#include "rt.h"


void	cb_obj_combo_type(GtkComboBox *box, gpointer data)
{
	t_env		*e;
	gint		index;

	e = data;
	index = gtk_combo_box_get_active(box);
	if (index == -1)
		gtk_widget_set_sensitive(e->ui->obj_nav_add_btn, FALSE);
	else if (index >= 0)
		gtk_widget_set_sensitive(e->ui->obj_nav_add_btn, TRUE);
}
