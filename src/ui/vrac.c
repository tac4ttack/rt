// fill cairo with random HUE
//cairo_set_source_rgb(cr, (double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX, (double)rand() / (double)RAND_MAX);


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
