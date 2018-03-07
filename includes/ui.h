#ifndef LINUX_KEYS_H
# define LINUX_KEYS_H

# include <gtk/gtk.h>

# define G_BYTE_ORDER G_LITTLE_ENDIAN

typedef	struct			s_ui
{
	int					gtk_status;
	int					redraw;
	
	GtkApplication		*gtk_app;
	GtkBuilder			*builder;
	GdkPixbuf			*icon;

	GtkWidget			*mainbox; // ?
	
	GtkWidget			*main_window;

	GtkWidget			*frame_box; // box containing frame_placeholder
	GdkPixbuf			*frame_pixel_buffer; // rendered scene gdkpixbuf
	GtkWidget			*frame_placeholder; // gtkimage widget
	guchar				*frame_ptr; // pointer to pixel data of pixbuf
}						t_ui;


#endif
