#ifndef UI_H
# define UI_H

# include "gtk/gtk.h"

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
	unsigned int	k_1 : 1;
	unsigned int		: 5;
}					t_keystate;

typedef	struct			s_ui
{
	int					gtkstatus;
	int					redraw;
	unsigned int		light_selector;
	cl_int4				render_pos;
	t_keystate			keys;

	// core
	GtkApplication		*app;
	GtkBuilder			*builder;
	
	// css
	GtkCssProvider		*css_provider;
//	GtkWidget			*menu_bar;
	
	GtkWidget			*main_window; //
	GtkAccelGroup			*main_window_accel;
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

						GtkWidget			*object_frame; //
							GtkWidget			*object_frame_label; //
							GtkWidget			*object_frame_align; //
								GtkWidget			*object_frame_box; //
									GtkWidget			*obj_list_box; //
										GtkWidget			*obj_list_id; //
											GtkWidget			*obj_list_id_label; //
										GtkWidget			*obj_list_pos; //
											GtkWidget			*obj_list_pos_box; //
												GtkWidget			*obj_list_pos_label; //
												GtkWidget			*obj_list_pos_spin_x; //
												GtkWidget			*obj_list_pos_spin_y; //
												GtkWidget			*obj_list_pos_spin_z; //
										GtkWidget			*obj_list_dir; //
											GtkWidget			*obj_list_dir_box; //
												GtkWidget			*obj_list_dir_label; //
												GtkWidget			*obj_list_dir_spin_x; //
												GtkWidget			*obj_list_dir_spin_y; //
												GtkWidget			*obj_list_dir_spin_z;  //
										GtkWidget			*obj_list_diff; //
											GtkWidget			*obj_list_diff_box; //
												GtkWidget			*obj_list_diff_label; //
												GtkWidget			*obj_list_diff_spin_x; //
												GtkWidget			*obj_list_diff_spin_y; //
												GtkWidget			*obj_list_diff_spin_z; //
										GtkWidget			*obj_list_spec; //
											GtkWidget			*obj_list_spec_box; //
												GtkWidget			*obj_list_spec_label; //
												GtkWidget			*obj_list_spec_spin_x; //
												GtkWidget			*obj_list_spec_spin_y; //
												GtkWidget			*obj_list_spec_spin_z; //
										GtkWidget			*obj_list_ref; //
											GtkWidget			*obj_list_ref_box; //
												GtkWidget			*obj_list_reflex_label; //
												GtkWidget			*obj_list_reflex_spin; //
												GtkWidget			*obj_list_refrac_label; //
												GtkWidget			*obj_list_refrac_spin; //
										GtkWidget			*obj_list_opacolor; //
											GtkWidget			*obj_list_opacolor_box; //
												GtkWidget			*obj_list_opacity_label; //
												GtkWidget			*obj_list_opacity_spin; //
												GtkWidget			*obj_list_color_label; //
												GtkWidget			* obj_list_color_btn; //
												GdkRGBA				obj_color; //

										GtkWidget			*obj_list_cone; //
											GtkWidget			*obj_list_cone_box; //
												GtkWidget			*obj_cone_angle_label; //
												GtkWidget			*obj_cone_angle_spin; //

										GtkWidget			*obj_list_cylinder; //
											GtkWidget			*obj_list_cylinder_box; //
												GtkWidget			*obj_cylinder_radius_label; //
												GtkWidget			*obj_cylinder_radius_spin; //
												GtkWidget			*obj_cylinder_height_label; //
												GtkWidget			*obj_cylinder_height_spin; //

										GtkWidget			*obj_list_ellipsoid; //
											GtkWidget			*obj_list_ellipsoid_box; //
												GtkWidget			*obj_ellipsoid_axis_label; //
												GtkWidget			*obj_ellipsoid_axis_spin_x; //
												GtkWidget			*obj_ellipsoid_axis_spin_y; //
												GtkWidget			*obj_ellipsoid_axis_spin_z; //
												GtkWidget			*obj_ellipsoid_radius_label; //
												GtkWidget			*obj_ellipsoid_radius_spin; //

										GtkWidget			*obj_list_paraboloid; //
											GtkWidget			*obj_list_paraboloid_box; //
												GtkWidget			*obj_paraboloid_first_box; //
													GtkWidget			*obj_paraboloid_height_label; //
													GtkWidget			*obj_paraboloid_height_spin; //
													GtkWidget			*obj_paraboloid_radius_label; //
													GtkWidget			*obj_paraboloid_radius_spin; //
												GtkWidget			*obj_paraboloid_second_box; //
													GtkWidget			*obj_paraboloid_basedir_label; //

										GtkWidget			*obj_list_plane; //
											GtkWidget			*obj_list_plane_box; //
												GtkWidget			*obj_plane_shit_label; //

										GtkWidget			*obj_list_sphere; //
											GtkWidget			*obj_list_sphere_box; //
												GtkWidget			*obj_sphere_radius_label; //
												GtkWidget			*obj_sphere_radius_spin; //

										GtkWidget			*obj_list_torus; //
											GtkWidget			*obj_list_torus_box; //
												GtkWidget			*obj_torus_lilradius_label; //
												GtkWidget			*obj_torus_lilradius_spin; //
												GtkWidget			*obj_torus_bigradius_label; //
												GtkWidget			*obj_torus_bigradius_spin; //


									GtkWidget			*obj_nav_box; //
										GtkWidget			*obj_nav_first; //
											GtkWidget			*obj_nav_prev_btn; //
											GtkWidget			*obj_nav_next_btn; //
											GtkWidget			*obj_nav_del_btn; //
										GtkWidget			*obj_nav_second; //
											GtkWidget			*obj_nav_add_label; //
											GtkWidget			*obj_nav_add_type_combo; //
											GtkWidget			*obj_nav_add_btn; //
										GtkWidget			*obj_nav_third; //
											GtkWidget			*obj_nav_jump_label; //
											GtkWidget			*obj_nav_jump_combo; //
						
						
						
						
						GtkWidget			*scene_frame; //
							GtkWidget			*scene_frame_label; //
							GtkWidget			*scene_frame_align; //
								GtkWidget			*scene_frame_box; //
									GtkWidget			*scene_resolution_box; //
										GtkWidget			*scene_resolution_label; //
										GtkWidget			*scene_resolution_width_spin; //
										GtkWidget			*scene_resolution_height_spin; //
									GtkWidget			*scene_ambient_box; //
										GtkWidget			*scene_ambient_label; //
										GtkWidget			*scene_ambient_red_spin; //
										GtkWidget			*scene_ambient_green_spin; //
										GtkWidget			*scene_ambient_blue_spin; //
									GtkWidget			*scene_depth_ss_box; //
										GtkWidget			*scene_depth_label; //
										GtkWidget			*scene_depth_spin; //
										GtkWidget			*scene_supersampling_label; //
										GtkWidget			*scene_supersampling_scale; //
									GtkWidget			*scene_postproc_box; //
										GtkWidget			*scene_postproc_label; //
										GtkWidget			*scene_postproc_bw_radio; //
										GtkWidget			*scene_postproc_sepia_radio; //
										GtkWidget			*scene_postproc_none_radio; //
										GtkWidget			*scene_postproc_invert_check; //

						GtkWidget			*cam_frame; //
							GtkWidget			*cam_frame_label; //
							GtkWidget			*cam_frame_align; //
								GtkWidget			*cam_frame_box; //
									GtkWidget			*cam_list_box; //
										GtkWidget			*cam_list_id; //
											GtkWidget			*cam_list_id_label; //
										GtkWidget			*cam_list_pos; // 
											GtkWidget			*cam_list_pos_box; // 
												GtkWidget			*cam_list_pos_label; // 
												GtkWidget			*cam_list_pos_spin_x; //
												GtkWidget			*cam_list_pos_spin_y; //
												GtkWidget			*cam_list_pos_spin_z; //
										GtkWidget			*cam_list_dir; //
											GtkWidget			*cam_list_dir_box; //
												GtkWidget			*cam_list_dir_label; //
												GtkWidget			*cam_list_dir_spin_x; //
												GtkWidget			*cam_list_dir_spin_y; // 
												GtkWidget			*cam_list_dir_spin_z;// 
										GtkWidget			*cam_list_fov; //
											GtkWidget			*cam_list_fov_box; // 
												GtkWidget			*cam_list_fov_label; // 
												GtkWidget			*cam_list_fov_spin; //
									GtkWidget			*cam_nav_box; //
										GtkWidget			*cam_nav_prev_btn; //
										GtkWidget			*cam_nav_next_btn; //
										GtkWidget			*cam_nav_add_btn; //
										GtkWidget			*cam_nav_del_btn; //

						GtkWidget			*light_frame; //		
							GtkWidget			*light_frame_label; //
							GtkWidget			*light_frame_align; //
								GtkWidget			*light_frame_box; // 
									GtkWidget			*light_list_box; // 
										GtkWidget			*light_list_id; //
											GtkWidget			*light_list_id_label; //
										GtkWidget			*light_list_pos; //
											GtkWidget			*light_list_pos_box; //
												GtkWidget			*light_list_pos_label; //
												GtkWidget			*light_list_pos_spin_x; //
												GtkWidget			*light_list_pos_spin_y; //
												GtkWidget			*light_list_pos_spin_z; //
										GtkWidget			*light_list_params; //
											GtkWidget			*light_list_params_box; // 
												GtkWidget			*light_list_bright_label; //
												GtkWidget			*light_list_bright_spin; //
												GtkWidget			*light_list_shrink_label; //
												GtkWidget			*light_list_shrink_spin; //
												GtkWidget			*light_list_color_label; //
												GtkWidget			* light_list_color_btn; //
												GdkRGBA				light_color; //
									GtkWidget			*light_nav_box; //
										GtkWidget			*light_nav_prev_btn; //
										GtkWidget			*light_nav_next_btn; //
										GtkWidget			*light_nav_add_btn; //
										GtkWidget			*light_nav_del_btn; //
					
											



			GtkWidget			*status_bar; //
			GtkWidget			*tool_bar; //
				GtkWidget			*tool_play_btn; //
				GtkWidget			*tool_stop_btn; //
				GtkWidget			*tool_render_btn; //
				GtkWidget			*tool_export_btn; //
				GtkWidget			*tool_about_btn; //
				GtkWidget			*tool_fps_placeholder; //
					GtkWidget			*tool_fps_label; //
	
	GtkWidget			*export_window; //	
	GtkWidget			*about_window; //
}						t_ui;

void					cb_about_btn(GtkButton *btn, gpointer data);

gboolean				cb_ambient_red_update(GtkSpinButton *spin, \
										gpointer data);
gboolean				cb_ambient_green_update(GtkSpinButton *spin, \
										gpointer data);
gboolean				cb_ambient_blue_update(GtkSpinButton *spin, \
										gpointer data);
gboolean				cb_cam_fov_update(GtkSpinButton *spin, gpointer data);
void					cb_cam_manage_add(GtkButton *btn, gpointer data);
void					cb_cam_manage_del(GtkButton *btn, gpointer data);
void					cb_cam_nav_prev(GtkButton *btn, gpointer data);
void					cb_cam_nav_next(GtkButton *btn, gpointer data);
gboolean				cb_cam_pos_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_cam_pos_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_cam_pos_z(GtkSpinButton *spin, gpointer data);
gboolean				cb_configure_draw_area(GtkWidget *widget, \
									GdkEventConfigure *event, gpointer data);
gboolean				cb_depth_update(GtkSpinButton *spin, gpointer data);
void					cb_export_btn(GtkButton *btn, gpointer data);

gboolean				cb_light_brightness(GtkSpinButton *spin, gpointer data);
void					cb_light_color(GtkColorButton *button, gpointer data);
void					cb_light_manage_del(GtkButton *btn, gpointer data);
void					cb_light_manage_add(GtkButton *btn, gpointer data);
void					cb_light_nav_prev(GtkButton *btn, gpointer data);
void					cb_light_nav_next(GtkButton *btn, gpointer data);
void					cb_light_nav_add(GtkButton *btn, gpointer data);
void					cb_light_nav_del(GtkButton *btn, gpointer data);
gboolean				cb_light_pos_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_light_pos_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_light_pos_z(GtkSpinButton *spin, gpointer data);
gboolean				cb_light_shrink(GtkSpinButton *spin, gpointer data);

void					cb_obj_color(GtkColorButton *button, gpointer data);
void					cb_obj_combo_type(GtkComboBox *box, gpointer data);
gboolean				cb_obj_diff_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_diff_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_diff_z(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_dir_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_dir_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_dir_z(GtkSpinButton *spin, gpointer data);
void					cb_obj_nav_add(GtkButton *btn, gpointer data);
void					cb_obj_nav_del(GtkButton *btn, gpointer data);
void					cb_obj_nav_next(GtkButton *btn, gpointer data);
void					cb_obj_nav_prev(GtkButton *btn, gpointer data);
gboolean				cb_obj_opacity(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_pos_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_pos_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_pos_z(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_reflex(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_refrac(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_spec_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_spec_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_spec_z(GtkSpinButton *spin, gpointer data);

void					cb_play_btn(GtkButton *btn, gpointer data);
void					cb_postproc_bw(GtkToggleButton *button, gpointer data);
void					cb_postproc_invert(GtkToggleButton *button, \
										gpointer data);
void					cb_postproc_none(GtkToggleButton *button, \
										gpointer data);
void					cb_postproc_sepia(GtkToggleButton *button, \
										gpointer data);
void					cb_render_btn(GtkButton *btn, gpointer data);
gboolean				cb_render_btnpress(GtkWidget *widget, GdkEvent *event, \
										gpointer data);
gboolean				cb_render_draw(GtkWidget *widget, cairo_t *cr, \
										gpointer data);
gboolean				cb_render_keypress(GtkWidget *widget, GdkEvent *event, \
										gpointer data);
gboolean				cb_render_keyrelease(GtkWidget *widget, \
										GdkEvent *event, gpointer data);
void					cb_render_update_size(GtkContainer *box, gpointer data);
gboolean				cb_res_height_update(GtkSpinButton *spin, gpointer data);
gboolean				cb_res_width_update(GtkSpinButton *spin, gpointer data);
void					cb_stop_btn(GtkButton *btn, gpointer data);
gboolean				cb_supersampling_update(GtkScale *scale, gpointer data);
gboolean				gtk_main_loop(gpointer data);
int						gtk_quit(GtkApplication *app, gpointer data);
void					init_gtk(GtkApplication* app, gpointer data);
GdkRGBA					int_to_gdkrbga(int color);
int						gdkrgba_to_int(GdkRGBA color);

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
# define KEY_STATE_1		e->ui->keys.k_1

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
# define KEY_1				49

#endif

