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

static void		gtk_export_png(GdkPixbuf *target, char *format, char *filename)
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

void		init_gtk(GtkApplication *app, t_env *e)
{
	ft_putendl("\n\n\x1b[1;32m/\\ Initializing GTK /\\\x1b[0m\n");
	
	e->ui->window = gtk_application_window_new(app);
	
	gtk_window_set_title(GTK_WINDOW(e->ui->window), "RT - Initializing...");
	gtk_window_set_resizable(GTK_WINDOW(e->ui->window), TRUE);
	gtk_window_set_default_size(GTK_WINDOW(e->ui->window), e->win_w + 200, e->win_h + 200);
	gtk_window_set_position(GTK_WINDOW(e->ui->window), GTK_WIN_POS_CENTER);
	g_signal_connect(GTK_WINDOW(e->ui->window), "destroy", G_CALLBACK(gtk_quit), (gpointer)e);
	g_signal_connect(G_OBJECT(e->ui->window), "key-release-event", G_CALLBACK(gtk_event_key_release), (gpointer)e);
	g_signal_connect(G_OBJECT(e->ui->window), "key-press-event", G_CALLBACK(gtk_event_key_press), (gpointer)e);
	g_signal_connect(G_OBJECT(e->ui->window), "button-release-event", G_CALLBACK(gtk_event_button_release), (gpointer)e);
	g_signal_connect(G_OBJECT(e->ui->window), "button-press-event", G_CALLBACK(gtk_event_button_press), (gpointer)e);

//// a pas l'air de fonctionner //////////////////////////////
////e->ui->icon = create_pixbuf_from_file(e, "icon.png");//////
////gtk_window_set_icon(GTK_WINDOW(e->ui->window), e->ui->icon);
//////////////////////////////////////////////////////////////

	e->ui->mainbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(e->ui->window), e->ui->mainbox);
	e->ui->frame_box = gtk_box_new(FALSE, 0);
	gtk_box_pack_start(GTK_BOX(e->ui->mainbox), e->ui->frame_box, TRUE, TRUE, 5);
//	gtk_container_add(GTK_CONTAINER(e->ui->window), e->ui->frame_box);

	e->ui->frame_placeholder = gtk_image_new();
	e->ui->frame_pixel_buffer = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, e->win_w, e->win_h);
	gtk_widget_set_size_request(e->ui->frame_placeholder, e->win_w, e->win_h);
	gtk_container_add(GTK_CONTAINER(e->ui->frame_box), e->ui->frame_placeholder);
		
	ft_putendl("\x1b[1;29mGTK successfully initialized\x1b[0m");

	ft_putendl("\n\n\x1b[1;32m/\\ Rendering first frame /\\\x1b[0m");
	ft_putendl("\n\x1b[1;29m...\x1b[0m\n");	
	opencl_draw(e);

//	printf("verif0 %x\n", e->frame_pixel_data[461312]);
//	printf("verif1 %x\n", e->ui->frame_ptr[461312]);

	e->ui->frame_ptr = gdk_pixbuf_get_pixels(e->ui->frame_pixel_buffer);
	ft_memcpy(e->ui->frame_ptr, e->pixel_data, (sizeof(int) * e->win_w * e->win_h));
	gtk_image_set_from_pixbuf(GTK_IMAGE(e->ui->frame_placeholder), e->ui->frame_pixel_buffer);

	printf("verif pixel data %x\n", e->pixel_data[461312]);
//	printf("test1 = %x\n", ((int*)e->frame_pixel_data)[461312]);
	printf("verif pixel buffer %x\n", ((int*)e->ui->frame_ptr)[461312]);

//	e->ui->frame_pixel_buffer = gdk_pixbuf_new_from_data((const guchar *)e->frame_pixel_data, GDK_COLORSPACE_RGB, 1, 8, e->win_w, e->win_h, e->win_w * 4, NULL, NULL);
//	e->ui->frame_pixel_buffer = gdk_pixbuf_new_from_bytes((GBytes *)e->frame_pixel_data, GDK_COLORSPACE_RGB, TRUE, 8, e->win_w, e->win_h, e->win_w * 4);
	gtk_export_png(e->ui->frame_pixel_buffer, "bmp", "testicule.bmp");


	ft_putendl("\x1b[1;29mDone!\x1b[0m");
	gtk_widget_show_all(e->ui->window);
}


/*void		init_gtk(GtkApplication *app, gpointer data)
{
	t_env *e;
	
	e = data;

	ft_putendl("\n\n\x1b[1;32m/\\ Initializing GTK /\\\x1b[0m\n");
	
	e->ui->window = gtk_application_window_new(app);
	
	gtk_window_set_title (GTK_WINDOW(e->ui->window), "RT - Initializing...");
	gtk_window_set_resizable(GTK_WINDOW(e->ui->window), TRUE);
	gtk_window_set_default_size(GTK_WINDOW(e->ui->window), e->win_w, e->win_h);
	gtk_window_set_position(GTK_WINDOW(e->ui->window), GTK_WIN_POS_CENTER);

	e->icon = create_pixbuf_from_file(e, "icon.png");
	gtk_window_set_icon(GTK_WINDOW(e->ui->window), e->icon);

	gtk_widget_show_all(e->ui->window);

	g_signal_connect(GTK_WINDOW(e->ui->window), "destroy", G_CALLBACK(gtk_quit), (gpointer)e);

	ft_putendl("\x1b[1;29mGTK successfully initialized\x1b[0m");
} */
