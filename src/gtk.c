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

void		gtk_export_png(GdkPixbuf *target, char *format, char *filename)
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
	pixbuf = gdk_pixbuf_new_from_bytes(buffer, GDK_COLORSPACE_RGB, 0, 8,
		 width , height, 4 * width);
	if (!pixbuf)
		return (NULL);
	g_bytes_unref(buffer);
	buffer = NULL;
	return (pixbuf);
}

void		init_gtk(t_env *e)
{
	t_ui		*ui;
	ui = e->ui;

	opencl_draw(e);

//	ui->builder = gtk_builder_new_from_file("lol.c");

//	ui->main_window = gtk_builder_get_object(ui->builder, "window");
//	ui->frame_placeholder = gtk_builder_get_object(ui->builder, "img");

	ui->main_window = (struct _GObject *)gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	e->ui->mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

	//gtk_window_set_title(GTK_WINDOW(ui->main_window), "RT - Initializing...");
	//gtk_window_set_resizable(GTK_WINDOW(ui->main_window), TRUE);
	//gtk_window_set_default_size(GTK_WINDOW(ui->main_window), e->win_w + 200, e->win_h + 200);
	//gtk_window_set_position(GTK_WINDOW(ui->main_window), GTK_WIN_POS_CENTER);
	//g_signal_connect(GTK_WINDOW(ui->main_window), "destroy", G_CALLBACK(gtk_quit), (gpointer)e);
	//g_signal_connect(G_OBJECT(ui->main_window), "key-release-event", G_CALLBACK(gtk_event_key_release), (gpointer)e);
	//g_signal_connect(G_OBJECT(ui->main_window), "key-press-event", G_CALLBACK(gtk_event_key_press), (gpointer)e);
	//g_signal_connect(G_OBJECT(ui->main_window), "button-release-event", G_CALLBACK(gtk_event_button_release), (gpointer)e);
	//g_signal_connect(G_OBJECT(ui->main_window), "button-press-event", G_CALLBACK(gtk_event_button_press), (gpointer)e);


	ui->pixbuf = gtk_new_image((unsigned char *)e->pixel_data, e->win_w, e->win_h);
	ui->frame_placeholder = (GObject*)gtk_image_new();
	gtk_image_set_from_pixbuf(GTK_IMAGE(e->ui->frame_placeholder), ui->pixbuf);

	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(e->ui->main_window), box);
	gtk_box_pack_start(GTK_BOX(box),
					GTK_WIDGET(ui->frame_placeholder ), FALSE, FALSE, 0);


	//g_timeout_add(1, gtk_main_loop, e);
	g_idle_add(gtk_main_loop, e);
	gtk_widget_show_all((GtkWidget*) e->ui->main_window);
	gtk_main();
}
