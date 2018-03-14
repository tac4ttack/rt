#include "rt.h"


gboolean cb_draw_render(GtkWidget *widget, cairo_t *cr, gpointer data)
{
	t_env *e;

	e = data;
	(void)widget;
	update_fps(&e->fps);
	opencl_draw(e);

	// check si je trempe bien le biscuit
//	ft_putendl("im in draw render");

	// 1ere methode
	gdk_cairo_set_source_pixbuf(cr, e->ui->pixbuf, 1, 1);

	// 2nde methode
//	if (e->ui->surface)
//		cairo_surface_destroy(e->ui->surface);
//	e->ui->surface = gdk_cairo_surface_create_from_pixbuf (e->ui->pixbuf, 1, NULL);
//	cairo_set_source_surface(cr, e->ui->surface, 0, 0);

	cairo_paint(cr);
	return FALSE;
}
