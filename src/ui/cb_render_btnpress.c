#include "rt.h"

gboolean cb_render_btnpress(GtkWidget *widget, GdkEvent  *event, gpointer data)
{
	t_env *e;

	(void)widget;
	(void)event;
	e = data;
	e->scene->flag |= OPTION_RUN;
	e->scene->mou_x = (int)event->button.x;
	e->scene->mou_y = (int)event->button.y;
	if (gtk_widget_is_focus (widget) == FALSE)
		gtk_widget_grab_focus(widget);
	return TRUE;
}
