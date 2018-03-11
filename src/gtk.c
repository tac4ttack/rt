#include "rt.h"

GdkPixbuf	*create_pixbuf_from_file(t_env *e, const gchar *filename)
{
	GdkPixbuf *pixbuf;
	GError *error;

	error = NULL;
	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if (!pixbuf)
	{
		ft_putstr(error->message);
		g_error_free(error);
		s_error("\x1b[1;31mCouldn't create GtkPixbuf from file\x1b[0m", e);
	}
	return pixbuf;
}

void		gtk_export(GdkPixbuf *target, char *format, char *filename)
{
	GError		*error;

	error = NULL;
	gdk_pixbuf_save(target, filename, format, &error, NULL);
	g_assert_no_error(error);
	ft_putstr("\x1b[1;29mFile\x1b[0m \x1b[1;33m");
	ft_putstr(filename);
	ft_putendl("\x1b[0m\x1b[1;29m successfully exported!\x1b[0m");
}

void gtk_event_key_release(GtkWidget *window, GdkEvent *event, gpointer data) // Gdk.EventKey
{
	t_env *e;

	(void)window;
	(void)event;
	e = data;
	ft_putendl("event key release");
}

void gtk_event_key_press(GtkWidget *window, GdkEvent *event, gpointer data) // Gdk.EventKey
{
	t_env *e;

	(void)window;
	(void)event;
	e = data;
	ft_putendl("event key press");
}

void gtk_event_button_release(GtkWidget *window, GdkEvent *event, gpointer data) // Gdk.EventButton
{
	t_env *e;

	(void)window;
	(void)event;
	e = data;
	ft_putendl("event button release");
}

void gtk_event_button_press(GtkWidget *window, GdkEvent *event, gpointer data) // Gdk.EventButton
{
	t_env *e;

	(void)window;
	(void)event;
	e = data;
	ft_putendl("event button press");
}

void gtk_stop_redraw(GtkWidget *window, GdkEvent *event, gpointer data)
{
	t_env *e;

	(void)window;
	(void)event;
	e = data;
	e->ui->redraw *= -1;
	printf("redraw = %d\n", e->ui->redraw);
}

GdkPixbuf		*gtk_new_image(unsigned char *data, int width, int height)
{
	GdkPixbuf	*pixbuf;
	GBytes		*buffer;

	buffer = NULL;
	pixbuf = NULL;
	buffer = g_bytes_new(data, width  * height * 4);
	pixbuf = gdk_pixbuf_new_from_bytes(buffer, GDK_COLORSPACE_RGB, TRUE, 8,
		 width , height, 4 * width);
	if (!pixbuf)
		return (NULL);
	g_bytes_unref(buffer);
	buffer = NULL;
	return (pixbuf);
}

void		init_gtk(GtkApplication* app, gpointer data)
{
	t_env *e;

	e = data;
	(void)app;
	ft_putendl("im in gtk init");
	
//	// css loading
//	e->ui->css = gtk_css_provider_new();
//	gtk_css_provider_load_from_path(e->ui->css, "./theme/gtk-dark.css", NULL);

	// init the builder and load the template
	e->ui->builder = gtk_builder_new();
	gtk_builder_add_from_file(e->ui->builder, "./theme/rt_ui.glade", NULL);

	// init and connect the main window
	e->ui->main_window = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_window"));
	g_signal_connect(e->ui->main_window, "destroy", G_CALLBACK(gtk_quit), (gpointer)e);

//	e->ui->drawing_area = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "drawing_area"));
//	gtk_widget_set_size_request(e->ui->drawing_area, 648, 480);
//	e->ui->cr = cairo_create(e->ui->surface);
//	cairo_set_source_rgb(e->ui->cr, 1, 1, 1);
//	cairo_paint(e->ui->cr);



	// init and activate all preset signals from template
	gtk_builder_connect_signals(e->ui->builder, NULL);
	
	// free the builder
	g_object_unref(e->ui->builder);

	gtk_widget_show_all(e->ui->main_window);
	
	gtk_main();
}
