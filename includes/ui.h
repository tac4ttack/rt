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
		GtkWidget			*main_box;
			GtkWidget			*main_panels;
			GtkWidget			*left_panel_scroll_win;
				GtkWidget			*left_panel_viewport;
					GtkWidget			*render;
					//	cairo_t				*cr; //useless ?
						cairo_surface_t		*surface;
						GdkPixbuf			*pixbuf;
			GtkWidget			*right_panel;
			GtkWidget			*status_bar;
			GtkWidget			*tool_bar;	
	
	



}						t_ui;

gboolean				gtk_main_loop(gpointer data);
int						gtk_quit(GtkApplication *app, gpointer data);
void					init_gtk(GtkApplication* app, gpointer data);

gboolean				cb_draw_render(GtkWidget *widget, cairo_t *cr, gpointer data);
gboolean				cb_configure_draw_area(GtkWidget *widget, \
									GdkEventConfigure *event, \
									gpointer data);

gboolean				cb_render_btnpress(GtkWidget *widget, \
											GdkEvent *event, gpointer data);
gboolean				cb_render_keypress(GtkWidget *widget, \
											GdkEvent *event, gpointer data);

#endif

