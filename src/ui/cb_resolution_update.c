#include "rt.h"



void		ui_update_resolution(t_env *e, int width, int height)
{
	e->scene->win_w = width;
	e->scene->win_h = height;
	free(e->pixel_data);

	if (!(e->pixel_data = malloc(sizeof(int) * e->scene->win_w * e->scene->win_h)))
		s_error("\x1b[1;31mCan't initialize new pixel buffer\x1b[0m", e);
	ft_bzero(e->pixel_data, sizeof(int) * e->scene->win_w * e->scene->win_h);

	if (!(cl_replace_buffer(e->cl, e->scene->win_w * e->scene->win_h * 4, 0)))
		s_error("\x1b[2;31mError creation new frame buffer cl_mem failed\x1b[0m", e);
	
	opencl_set_args(e, e->cl);

//	g_object_unref(e->ui->pixbuf);
	e->ui->pixbuf = gdk_pixbuf_new_from_data((const guchar *)e->pixel_data, GDK_COLORSPACE_RGB, 1, 8, e->scene->win_w, e->scene->win_h, e->scene->win_w * 4, NULL, NULL);
	e->ui->surface = NULL;
//	printf("new width = %d | height = %d\n", gdk_pixbuf_get_width (e->ui->pixbuf), gdk_pixbuf_get_height(e->ui->pixbuf));
//	cb_configure_draw_area(NULL, NULL, (gpointer)e);
//	opencl_draw(e);
}

gboolean	cb_width_update(GtkSpinButton *spin, gpointer data)
{
	gint 	value;
	t_env *e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	printf("width has changed! it was %d, it is now %d\n", e->scene->win_w, (int)value);
	e->ui->redraw = 0;
	ui_update_resolution(e, value, e->scene->win_h);
	e->ui->redraw = 1;
	return FALSE;
}


gboolean	cb_height_update(GtkSpinButton *spin, gpointer data)
{
	gint 	value;
	t_env *e;

	e = data;
	value = gtk_spin_button_get_value_as_int(spin);
	printf("height has changed! it was %d, it is now %d\n", e->scene->win_h, (int)value);
	e->ui->redraw = 0;
	ui_update_resolution(e, e->scene->win_w, value);
	e->ui->redraw = 1;
	return FALSE;
}
