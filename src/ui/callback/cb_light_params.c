#include "rt.h"

gboolean		cb_light_shrink(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	ACTIVELIGHT.shrink = value;
	return TRUE;
}

gboolean		cb_light_brightness(GtkSpinButton *spin, gpointer data)
{
	gdouble 	value;
	t_env 		*e;

	e = data;
	value = gtk_spin_button_get_value(spin);
	ACTIVELIGHT.brightness = (float)value;
	return TRUE;
}

void			cb_light_color(GtkColorButton *button, gpointer data)
{
	t_env 		*e;
	GdkRGBA		new_color;
	
	e = data;
	new_color.alpha = 1;
	gtk_color_chooser_get_rgba(GTK_COLOR_CHOOSER(button), &new_color);
	ACTIVELIGHT.color = gdkrgba_to_int(new_color);
	e->ui->light_color = new_color;
	
}
