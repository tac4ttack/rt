#ifndef LINUX_KEYS_H
# define LINUX_KEYS_H

# include <gtk/gtk.h>

# define G_BYTE_ORDER G_LITTLE_ENDIAN

typedef	struct			s_ui
{
	int					gtk_status;
	int					redraw;

	GdkPixbuf			*icon;

	GtkWidget			*mainbox; // ?

	GObject				*main_window;

	GtkWidget			*frame_box; // box containing frame_placeholder
	GdkPixbuf			*frame_pixel_buffer; // rendered scene gdkpixbuf
	GObject				*frame_placeholder; // gtkimage widget
	guchar				*frame_ptr; // pointer to pixel data of pixbuf
	GtkBuilder			*builder;
	GdkPixbuf			*pixbuf;
	guchar				*pixbuf_data;
}						t_ui;

GdkPixbuf		*gtk_new_image(unsigned char *data, int width, int height);

#endif
