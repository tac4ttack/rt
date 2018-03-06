#include "rt.h"

GdkPixbuf	*create_pixbuf_from_file(t_env *e, const gchar *filename)
{    
	GdkPixbuf *pixbuf;
	GError *error = NULL;

	pixbuf = gdk_pixbuf_new_from_file(filename, &error);
	if (!pixbuf)
	{  
		ft_putstr(error->message);
		g_error_free(error);
		s_error("\x1b[1;31mCouldn't create GtkPixbuf from file\x1b[0m", e);
	}
	return pixbuf;
}

void gtk_stop_redraw(GtkWidget *window, gpointer data)
{
	t_env *e;

	(void)window;
	e = data;
	e->redraw *= -1;
	printf("redraw = %d\n", e->redraw);
}

void		init_gtk(GtkApplication *app, t_env *e)
{
	ft_putendl("\n\n\x1b[1;32m/\\ Initializing GTK /\\\x1b[0m\n");
	
	e->window = gtk_application_window_new(app);
	
	gtk_window_set_title(GTK_WINDOW(e->window), "RT - Initializing...");
	gtk_window_set_resizable(GTK_WINDOW(e->window), TRUE);
	gtk_window_set_default_size(GTK_WINDOW(e->window), e->win_w, e->win_h);
	gtk_window_set_position(GTK_WINDOW(e->window), GTK_WIN_POS_CENTER);

	// a pas l'air de fonctionner
	e->icon = create_pixbuf_from_file(e, "icon.png");
	gtk_window_set_icon(GTK_WINDOW(e->window), e->icon);
	/////////////////////////////////////////////////////

	g_signal_connect(GTK_WINDOW(e->window), "destroy", G_CALLBACK(gtk_quit), (gpointer)e);
	g_signal_connect(GTK_WINDOW(e->window), "clicked", G_CALLBACK(gtk_stop_redraw), (gpointer)e);

	e->frame_box = gtk_box_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(e->window), e->frame_box);

	ft_putendl("\x1b[1;32mGTK successfully initialized\x1b[0m");

	ft_putendl("\n\n\x1b[1;32m/\\ Rendering first frame /\\\x1b[0m");
	ft_putendl("\x1b[1;32m...\x1b[0m");	
	opencl_draw(e);	
	ft_putendl("\x1b[1;32mDone!\x1b[0m");
	gtk_widget_show_all(e->window);
}


/*void		init_gtk(GtkApplication *app, gpointer data)
{
	t_env *e;
	
	e = data;

	ft_putendl("\n\n\x1b[1;32m/\\ Initializing GTK /\\\x1b[0m\n");
	
	e->window = gtk_application_window_new(app);
	
	gtk_window_set_title (GTK_WINDOW(e->window), "RT - Initializing...");
	gtk_window_set_resizable(GTK_WINDOW(e->window), TRUE);
	gtk_window_set_default_size(GTK_WINDOW(e->window), e->win_w, e->win_h);
	gtk_window_set_position(GTK_WINDOW(e->window), GTK_WIN_POS_CENTER);

	e->icon = create_pixbuf_from_file(e, "icon.png");
	gtk_window_set_icon(GTK_WINDOW(e->window), e->icon);

	gtk_widget_show_all(e->window);

	g_signal_connect(GTK_WINDOW(e->window), "destroy", G_CALLBACK(gtk_quit), (gpointer)e);

	ft_putendl("\x1b[1;32mGTK successfully initialized\x1b[0m");
} */
