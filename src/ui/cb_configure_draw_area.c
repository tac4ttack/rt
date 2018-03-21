#include "rt.h"


void		clear_surface(t_env *e)
{
	cairo_t	*cr;

	cr = cairo_create(e->ui->surface);
	cairo_set_source_rgb(cr, 0, 0, 0);
	cairo_paint(cr);
	cairo_destroy(cr);
}


gboolean		cb_configure_draw_area(GtkWidget *widget, \
									GdkEventConfigure *event, \
									gpointer data)
{
	t_env *e;

	e = data;
	(void)event;
	if (e->ui->surface)
		cairo_surface_destroy(e->ui->surface);
	e->ui->surface = gdk_window_create_similar_surface(\
						gtk_widget_get_window(widget), \
						CAIRO_CONTENT_COLOR, \
						gtk_widget_get_allocated_width(widget), \
						gtk_widget_get_allocated_height(widget));
	clear_surface(e);
	return TRUE;
}
