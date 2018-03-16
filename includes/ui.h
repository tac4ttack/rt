#ifndef UI_H
# define UI_H

# include <gtk/gtk.h>

typedef struct		s_keystate
{
	unsigned int	k_up : 1;
	unsigned int	k_down : 1;
	unsigned int	k_left : 1;
	unsigned int	k_right : 1;
	unsigned int	k_esc : 1;
	unsigned int	k_space : 1;
	unsigned int	k_nplus : 1;
	unsigned int	k_nminus : 1;
	unsigned int	k_n4 : 1;
	unsigned int	k_n5 : 1;
	unsigned int	k_n6 : 1;
	unsigned int	k_n7 : 1;
	unsigned int	k_n8 : 1;
	unsigned int	k_n9 : 1;
	unsigned int	k_w : 1;
	unsigned int	k_a : 1;
	unsigned int	k_s : 1;
	unsigned int	k_d : 1;
	unsigned int	k_c : 1;
	unsigned int	k_i : 1;
	unsigned int	k_j : 1;
	unsigned int	k_k : 1;
	unsigned int	k_l : 1;
	unsigned int	k_u : 1;
	unsigned int	k_o : 1;
	unsigned int	k_z : 1;
	unsigned int		: 6;
}					t_keystate;

typedef struct			s_widget_list
{
	GtkWidget			*main_window; //
			GtkWidget			*main_box; //
				GtkWidget			*main_panels;

					GtkWidget			*left_panel_scroll; //
						GtkWidget			*left_panel_viewport; //
							GtkWidget			*render; //
							
					GtkWidget			*right_panel_scroll; //
						GtkWidget			*right_panel_viewport; //
							GtkWidget			*right_panel; //

								GtkWidget			*scene_resolution_box;
									GtkWidget			*scene_resolution_width_spin;
									GtkWidget			*scene_resolution_height_spin;
							
								GtkWidget			*scene_ambient_box;
									GtkWidget			*scene_ambient_red_spin;
									GtkWidget			*scene_ambient_green_spin;
									GtkWidget			*scene_ambient_blue_spin;
							
								GtkWidget			*scene_depth_box;
									GtkWidget			*scene_depth_spin;

								GtkWidget			*scene_postproc_box;
									GtkWidget			*scene_postproc_bw_radio;
									GtkWidget			*scene_postproc_sepia_radio;
									GtkWidget			*scene_postproc_none_radio;

				GtkWidget			*status_bar;
				GtkWidget			*tool_bar;	
}						t_widget_list;

typedef	struct			s_ui
{
	int					gtkstatus;
	int					redraw;
	t_keystate			keys;

	// core
	GtkApplication		*app;
	GtkBuilder			*builder;
	
	// css
	GtkCssProvider		*style_provider;

	GtkWidget			*main_window; //
		GtkWidget			*main_box; //
			GtkWidget			*main_panels;

				GtkWidget			*left_panel_scroll; //
					GtkWidget			*left_panel_viewport; //
						GtkWidget			*render; //
						//	cairo_t				*cr; //useless ?
							cairo_surface_t		*surface;  //
							GdkPixbuf			*pixbuf; //

				GtkWidget			*right_panel_scroll; //
					GtkWidget			*right_panel_viewport; //
						GtkWidget			*right_panel; //

							GtkWidget			*scene_resolution_box;
								GtkWidget			*scene_resolution_width_spin;
								GtkWidget			*scene_resolution_height_spin;
						
							GtkWidget			*scene_ambient_box;
								GtkWidget			*scene_ambient_red_spin;
								GtkWidget			*scene_ambient_green_spin;
								GtkWidget			*scene_ambient_blue_spin;
						
							GtkWidget			*scene_depth_box;
								GtkWidget			*scene_depth_spin;

							GtkWidget			*scene_postproc_box;
								GtkWidget			*scene_postproc_bw_radio;
								GtkWidget			*scene_postproc_sepia_radio;
								GtkWidget			*scene_postproc_none_radio;

			GtkWidget			*status_bar;
			GtkWidget			*tool_bar;	
	
}						t_ui;

void					init_gtk(GtkApplication* app, gpointer data);
gboolean				gtk_main_loop(gpointer data);
int						gtk_quit(GtkApplication *app, gpointer data);


gboolean				cb_draw_render(GtkWidget *widget, cairo_t *cr, gpointer data);
gboolean				cb_configure_draw_area(GtkWidget *widget, \
									GdkEventConfigure *event, \
									gpointer data);

gboolean				cb_render_btnpress(GtkWidget *widget, \
											GdkEvent *event, gpointer data);
gboolean				cb_render_keypress(GtkWidget *widget, \
											GdkEvent *event, gpointer data);
gboolean				cb_render_keyrelease(GtkWidget *widget, \
											GdkEvent *event, gpointer data);

# define KEY_STATE_UA		e->ui->keys.k_up
# define KEY_STATE_DA		e->ui->keys.k_down
# define KEY_STATE_LA		e->ui->keys.k_left
# define KEY_STATE_RA		e->ui->keys.k_right
# define KEY_STATE_ESC		e->ui->keys.k_esc
# define KEY_STATE_SPC		e->ui->keys.k_space
# define KEY_STATE_NPLU		e->ui->keys.k_nplus
# define KEY_STATE_NMIN		e->ui->keys.k_nminus
# define KEY_STATE_N7		e->ui->keys.k_n7
# define KEY_STATE_N8		e->ui->keys.k_n8
# define KEY_STATE_N9		e->ui->keys.k_n9
# define KEY_STATE_N4		e->ui->keys.k_n4
# define KEY_STATE_N5		e->ui->keys.k_n5
# define KEY_STATE_N6		e->ui->keys.k_n6
# define KEY_STATE_W		e->ui->keys.k_w
# define KEY_STATE_A		e->ui->keys.k_a
# define KEY_STATE_S		e->ui->keys.k_s
# define KEY_STATE_D		e->ui->keys.k_d
# define KEY_STATE_C		e->ui->keys.k_c
# define KEY_STATE_I		e->ui->keys.k_i
# define KEY_STATE_J		e->ui->keys.k_j
# define KEY_STATE_K		e->ui->keys.k_k
# define KEY_STATE_L		e->ui->keys.k_l
# define KEY_STATE_U		e->ui->keys.k_u
# define KEY_STATE_O		e->ui->keys.k_o
# define KEY_STATE_Z		e->ui->keys.k_z

# define KEY_UA				65362
# define KEY_DA				65364
# define KEY_LA				65361
# define KEY_RA				65363
# define KEY_ESC			65307
# define KEY_SPC			32
# define KEY_NPLU			65451
# define KEY_NMIN			65453
# define KEY_N7				65463
# define KEY_N8				65464
# define KEY_N9				65465
# define KEY_N4				65460
# define KEY_N5				65461
# define KEY_N6				65462
# define KEY_W				119
# define KEY_A				97
# define KEY_S				115
# define KEY_D				100
# define KEY_C				99
# define KEY_I				105
# define KEY_J				106
# define KEY_K				107
# define KEY_L				108
# define KEY_U				117
# define KEY_O				111
# define KEY_Z				122

#endif

