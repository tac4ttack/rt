#include "rt.h"

gboolean cb_render_btnpress(GtkWidget *widget, GdkEvent  *event, gpointer data)
{
	(void)widget;
	(void)event;
	t_env *e;


	e = data;
//	gtk_widget_grab_focus(widget);
	ft_putendl("test btnpress");
	return TRUE;
}
