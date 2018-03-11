#ifndef LINUX_KEYS_H
# define LINUX_KEYS_H

# include <gtk/gtk.h>

# define G_BYTE_ORDER G_LITTLE_ENDIAN

typedef	struct			s_ui
{
	int					gtkstatus;
	int					redraw;

	// core
	GtkApplication		*app;
	GtkBuilder			*builder;
	
	// css
	GtkCssProvider		*style_provider;

	GtkWidget			*main_window;
	GtkWidget			*drawing_area;

	cairo_t				*cr;
	cairo_surface_t		*surface;

	
}						t_ui;

GdkPixbuf		*gtk_new_image(unsigned char *data, int width, int height);

#endif
