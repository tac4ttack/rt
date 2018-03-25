#include "rt.h"


gboolean cb_render_draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	t_env *e;
	(void)widget;
	e = data;

//	1ere methode
	gdk_cairo_set_source_pixbuf(cr, e->ui->pixbuf, 0, 0);
//	2nde methode
	// if (e->ui->surface)
	// 	cairo_surface_destroy(e->ui->surface);
	// e->ui->surface = gdk_cairo_surface_create_from_pixbuf (e->ui->pixbuf, 1, NULL);
	// cairo_set_source_surface(cr, e->ui->surface, 0, 0);

	cairo_paint(cr);
	return FALSE;
}
