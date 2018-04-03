/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ui.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 18:49:38 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/03 14:56:38 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "gtk/gtk.h"

typedef struct			s_keystate
{
	unsigned int		k_up : 1;
	unsigned int		k_down : 1;
	unsigned int		k_left : 1;
	unsigned int		k_right : 1;
	unsigned int		k_esc : 1;
	unsigned int		k_space : 1;
	unsigned int		k_nplus : 1;
	unsigned int		k_nminus : 1;
	unsigned int		k_n4 : 1;
	unsigned int		k_n5 : 1;
	unsigned int		k_n6 : 1;
	unsigned int		k_n7 : 1;
	unsigned int		k_n8 : 1;
	unsigned int		k_n9 : 1;
	unsigned int		k_w : 1;
	unsigned int		k_a : 1;
	unsigned int		k_s : 1;
	unsigned int		k_d : 1;
	unsigned int		k_c : 1;
	unsigned int		k_i : 1;
	unsigned int		k_j : 1;
	unsigned int		k_k : 1;
	unsigned int		k_l : 1;
	unsigned int		k_u : 1;
	unsigned int		k_o : 1;
	unsigned int		k_z : 1;
	unsigned int		k_1 : 1;
	unsigned int		dummy : 5;
}						t_keystate;

typedef	struct			s_ui
{
	int					gtkstatus;
	int					redraw;
	unsigned int		light_selector;
	cl_int4				render_pos;
	t_keystate			keys;
	GtkApplication		*app;
	GtkBuilder			*builder;
	GtkCssProvider		*css_provider;
	GtkWidget			*main_window;
	GtkWidget			*render;
	cairo_surface_t		*surface;
	GdkPixbuf			*pixbuf;
	GtkWidget			*obj_list_box;
	GtkWidget			*obj_list_id_label;
	GtkWidget			*obj_list_pos_spin_x;
	GtkWidget			*obj_list_pos_spin_y;
	GtkWidget			*obj_list_pos_spin_z;
	GtkWidget			*obj_list_dir_spin_x;
	GtkWidget			*obj_list_dir_spin_y;
	GtkWidget			*obj_list_dir_spin_z;
	GtkWidget			*obj_list_diff_spin_x;
	GtkWidget			*obj_list_diff_spin_y;
	GtkWidget			*obj_list_diff_spin_z;
	GtkWidget			*obj_list_spec_spin_x;
	GtkWidget			*obj_list_spec_spin_y;
	GtkWidget			*obj_list_spec_spin_z;
	GtkWidget			*obj_list_reflex_spin;
	GtkWidget			*obj_list_refrac_spin;
	GtkWidget			*obj_list_opacity_spin;
	GtkWidget			* obj_list_color_btn;
	GdkRGBA				obj_color;
	GtkWidget			*obj_list_flag_waves_check;
	GtkWidget			*obj_list_flag_diff_check;
	GtkWidget			*obj_list_flag_checkboard_check;
	GtkWidget			*obj_list_cone;
	GtkWidget			*obj_cone_angle_spin;
	GtkWidget			*obj_list_cylinder;
	GtkWidget			*obj_cylinder_radius_spin;
	GtkWidget			*obj_cylinder_height_spin;
	GtkWidget			*obj_list_ellipsoid;
	GtkWidget			*obj_ellipsoid_axis_spin_x;
	GtkWidget			*obj_ellipsoid_axis_spin_y;
	GtkWidget			*obj_ellipsoid_axis_spin_z;
	GtkWidget			*obj_ellipsoid_radius_label;
	GtkWidget			*obj_ellipsoid_radius_spin;
	GtkWidget			*obj_list_plane;
	GtkWidget			*obj_list_sphere;
	GtkWidget			*obj_sphere_radius_spin;
	GtkWidget			*obj_list_torus;
	GtkWidget			*obj_torus_lilradius_spin;
	GtkWidget			*obj_torus_bigradius_spin;
	
	GtkWidget			*obj_limit_button; //
	GtkWidget			*obj_limit_dir_spin_x; //
	GtkWidget			*obj_limit_dir_spin_y; //
	GtkWidget			*obj_limit_dir_spin_z; //
	GtkWidget			*obj_limit_pos_spin_x; //
	GtkWidget			*obj_limit_pos_spin_y; //
	GtkWidget			*obj_limit_pos_spin_z;//
	
	GtkWidget			*obj_sinwave_button; //
	GtkWidget			*obj_sinwave_param1_spin_x; //
	GtkWidget			*obj_sinwave_param1_spin_y; //
	GtkWidget			*obj_sinwave_param1_spin_z; //
	GtkWidget			*obj_sinwave_param2_spin_x; //
	GtkWidget			*obj_sinwave_param2_spin_y; //
	GtkWidget			*obj_sinwave_param2_spin_z; //

	GtkWidget			*obj_list_checkboard; //
	GtkWidget			*obj_checkboard_button; //
	GtkWidget			*obj_checkboard_width_spin; //
	GtkWidget			*obj_checkboard_height_spin; //
	
	GtkWidget			*obj_list_texture_diff; //
	GtkWidget			*obj_texture_diff_button; //
	GtkWidget			*obj_texture_diff_offset_spin_x; //
	GtkWidget			*obj_texture_diff_offset_spin_y; //
	GtkWidget			*obj_texture_diff_ratio_spin; //
	GtkWidget			*obj_texture_diff_chooser; //
	
	GtkWidget			*obj_nav_prev_btn;
	GtkWidget			*obj_nav_next_btn;
	GtkWidget			*obj_nav_del_btn;
	GtkWidget			*obj_nav_add_type_combo;
	GtkWidget			*obj_nav_add_btn;
	GtkWidget			*obj_nav_jump_combo;
	GtkWidget			*scene_resolution_width_spin;
	GtkWidget			*scene_resolution_height_spin;
	GtkWidget			*scene_ambient_red_spin;
	GtkWidget			*scene_ambient_green_spin;
	GtkWidget			*scene_ambient_blue_spin;
	GtkWidget			*scene_depth_spin;
	GtkWidget			*scene_supersampling_scale;
	GtkWidget			*scene_postproc_bw_radio;
	GtkWidget			*scene_postproc_sepia_radio;
	GtkWidget			*scene_postproc_none_radio;
	GtkWidget			*scene_postproc_invert_check;
	GtkWidget			*scene_cartoon_four_radio;
	GtkWidget			*scene_cartoon_two_radio;
	GtkWidget			*cam_list_id_label;
	GtkWidget			*cam_list_pos_spin_x;
	GtkWidget			*cam_list_pos_spin_y;
	GtkWidget			*cam_list_pos_spin_z;
	GtkWidget			*cam_list_dir_spin_x;
	GtkWidget			*cam_list_dir_spin_y;
	GtkWidget			*cam_list_dir_spin_z;
	GtkWidget			*cam_list_fov_spin;
	GtkWidget			*cam_nav_prev_btn;
	GtkWidget			*cam_nav_next_btn;
	GtkWidget			*cam_nav_add_btn;
	GtkWidget			*cam_nav_del_btn;
	GtkWidget			*light_list_id_label;
	GtkWidget			*light_list_pos_spin_x;
	GtkWidget			*light_list_pos_spin_y;
	GtkWidget			*light_list_pos_spin_z;
	GtkWidget			*light_list_bright_spin;
	GtkWidget			*light_list_shrink_spin;
	GtkWidget			* light_list_color_btn;
	GdkRGBA				light_color;
	GtkWidget			*light_nav_prev_btn;
	GtkWidget			*light_nav_next_btn;
	GtkWidget			*light_nav_add_btn;
	GtkWidget			*light_nav_del_btn;
	GtkWidget			*tool_play_btn;
	GtkWidget			*tool_stop_btn;
	GtkWidget			*tool_render_btn;
	GtkWidget			*tool_export_btn;
	GtkWidget			*tool_about_btn;
	GtkWidget			*tool_fps_label;
	GtkWidget			*export_window;
	GtkWidget			*about_window;
}						t_ui;

void					cb_about_btn(GtkButton *btn, gpointer data);

gboolean				cb_ambient_red_update(GtkSpinButton *spin, \
										gpointer data);
gboolean				cb_ambient_green_update(GtkSpinButton *spin, \
										gpointer data);
gboolean				cb_ambient_blue_update(GtkSpinButton *spin, \
										gpointer data);
gboolean				cb_cam_dir_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_cam_dir_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_cam_dir_z(GtkSpinButton *spin, gpointer data);
gboolean				cb_cam_fov_update(GtkSpinButton *spin, gpointer data);
void					cb_cam_manage_add(GtkButton *btn, gpointer data);
void					cb_cam_manage_del(GtkButton *btn, gpointer data);
void					cb_cam_nav_prev(GtkButton *btn, gpointer data);
void					cb_cam_nav_next(GtkButton *btn, gpointer data);
gboolean				cb_cam_pos_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_cam_pos_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_cam_pos_z(GtkSpinButton *spin, gpointer data);

void					cb_cartoon_two(GtkToggleButton *button, gpointer data);
void					cb_cartoon_four(GtkToggleButton *button, gpointer data);

gboolean				cb_cone_angle(GtkSpinButton *spin, gpointer data);

gboolean				cb_configure_draw_area(GtkWidget *widget, \
									GdkEventConfigure *event, gpointer data);

gboolean				cb_cylinder_radius(GtkSpinButton *spin, gpointer data);

gboolean				cb_depth_update(GtkSpinButton *spin, gpointer data);

gboolean				cb_ellipsoid_axis_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_ellipsoid_axis_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_ellipsoid_axis_z(GtkSpinButton *spin, gpointer data);
gboolean				cb_ellipsoid_radius(GtkSpinButton *spin, gpointer data);

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

void					cb_obj_checkboard_check(GtkButton *btn, gpointer data);
void					cb_obj_color(GtkColorButton *button, gpointer data);
void					cb_obj_combo_type(GtkComboBox *box, gpointer data);
void					cb_obj_diff_check(GtkButton *btn, gpointer data);
gboolean				cb_obj_diff_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_diff_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_diff_z(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_dir_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_dir_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_obj_dir_z(GtkSpinButton *spin, gpointer data);
void					cb_obj_jump_combo(GtkComboBox *box, gpointer data);
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
void					cb_obj_wave_check(GtkButton *btn, gpointer data);

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
gboolean				cb_render_btnrelease(GtkWidget *widget, GdkEvent *ev, \
											gpointer data);
gboolean				cb_render_draw(GtkWidget *widget, cairo_t *cr, \
										gpointer data);
gboolean				cb_render_keypress(GtkWidget *widget, GdkEvent *event, \
										gpointer data);
gboolean				cb_render_keyrelease(GtkWidget *widget, \
										GdkEvent *event, gpointer data);
void					cb_render_update_size(GtkContainer *box, gpointer data);
gboolean				cb_res_heigh_update(GtkSpinButton *spin, gpointer data);
gboolean				cb_res_width_update(GtkSpinButton *spin, gpointer data);

gboolean				cb_sphere_radius(GtkSpinButton *spin, gpointer data);

void					cb_stop_btn(GtkButton *btn, gpointer data);
gboolean				cb_supersampling_update(GtkScale *scale, gpointer data);

gboolean				cb_torus_radius_lil(GtkSpinButton *spin, gpointer data);
gboolean				cb_torus_radius_big(GtkSpinButton *spin, gpointer data);

gboolean				cb_waves_p1_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_waves_p1_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_waves_p1_z(GtkSpinButton *spin, gpointer data);
gboolean				cb_waves_p2_x(GtkSpinButton *spin, gpointer data);
gboolean				cb_waves_p2_y(GtkSpinButton *spin, gpointer data);
gboolean				cb_waves_p2_z(GtkSpinButton *spin, gpointer data);

gboolean				gtk_main_loop(gpointer data);
int						gtk_quit(GtkApplication *app, gpointer data);
void					init_gtk(GtkApplication *app, gpointer data);
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
