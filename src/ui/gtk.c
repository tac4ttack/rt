#include "rt.h"

void		init_gtk_main_widgets(t_env *e)
{
////MAIN WINDOW
	// init and connect the main window
	e->ui->main_window = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_window"));
//	e->ui->main_window_accel = gtk_accel_group_new();
//	gtk_window_add_accel_group(GTK_WINDOW(e->ui->main_window), e->ui->main_window_accel);

//	e->ui->menu_bar = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "menu_bar"));
//	gtk_widget_hide(e->ui->menu_bar);
//	gtk_mac_menu_set_menu_bar(GTK_MENU_SHELL(e->ui->menu_bar));

////MAIN PANEL	
	// init all widget in order
	e->ui->main_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_box"));
	e->ui->main_panels = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_panels"));

////LEFT PANEL
	e->ui->left_panel_scroll = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "left_panel_scroll"));
	e->ui->left_panel_viewport = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "left_panel_viewport"));
	// init render shit
	e->ui->render = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "render"));
	gtk_widget_set_size_request(e->ui->render, e->scene->win_w, e->scene->win_h);
	e->ui->pixbuf = gdk_pixbuf_new_from_data((const guchar *)e->pixel_data, GDK_COLORSPACE_RGB, 1, 8, e->scene->win_w, e->scene->win_h, e->scene->win_w * 4, NULL, NULL);
	e->ui->surface = NULL;
////RIGHT PANEL
	e->ui->right_panel_scroll = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "right_panel_scroll"));
	e->ui->right_panel_viewport = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "right_panel_viewport"));
	e->ui->right_panel = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "right_panel"));
}

void		init_gtk_scene_widgets(t_env *e)
{
/////SCENE/////
	e->ui->scene_frame = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_frame"));
	e->ui->scene_frame_align = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_frame_align"));
	e->ui->scene_frame_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_frame_label"));
	e->ui->scene_frame_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_frame_box"));
	// scene resolution shit
	e->ui->scene_resolution_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_resolution_box"));
	e->ui->scene_resolution_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_resolution_label"));
	e->ui->scene_resolution_width_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_resolution_width_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_resolution_width_spin, (gdouble)e->scene->win_w);
	e->ui->scene_resolution_height_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_resolution_height_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_resolution_height_spin, (gdouble)e->scene->win_h);
	// scene ambient shit
	e->ui->scene_ambient_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_ambient_box"));
	e->ui->scene_ambient_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_ambient_label"));
	e->ui->scene_ambient_red_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_ambient_red_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_ambient_red_spin, (gdouble)e->scene->ambient.x);
	e->ui->scene_ambient_green_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_ambient_green_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_ambient_green_spin, (gdouble)e->scene->ambient.y);
	e->ui->scene_ambient_blue_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_ambient_blue_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_ambient_blue_spin, (gdouble)e->scene->ambient.z);
	
	// scene supersampling & depth shit
	e->ui->scene_depth_ss_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_depth_ss_box"));
	// scene depth shit
	e->ui->scene_depth_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_depth_label"));
	e->ui->scene_depth_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_depth_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_depth_spin, (gdouble)e->scene->depth);
	// scene supersampling shit
	e->ui->scene_supersampling_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_supersampling_label"));
	e->ui->scene_supersampling_scale = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_supersampling_scale"));
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), 1, GTK_POS_BOTTOM, "x1");
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), 2, GTK_POS_BOTTOM, "x2");
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), 3, GTK_POS_BOTTOM, "x4");
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), 4, GTK_POS_BOTTOM, "x8");
	gtk_scale_add_mark(GTK_SCALE(e->ui->scene_supersampling_scale), 5, GTK_POS_BOTTOM, "x16");
	
	// scene post proc shit
	e->ui->scene_postproc_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_postproc_box"));
	e->ui->scene_postproc_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_postproc_label"));
	e->ui->scene_postproc_bw_radio = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_postproc_bw_radio"));
	e->ui->scene_postproc_sepia_radio = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_postproc_sepia_radio"));
	e->ui->scene_postproc_none_radio = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_postproc_none_radio"));
	e->ui->scene_postproc_invert_check = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_postproc_invert_check"));
}

void		init_gtk(GtkApplication* app, gpointer data)
{
	t_env *e;

	e = data;
	(void)app;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));


	printf("base target is %d\n", e->target);


////CSS STYLING
	e->ui->css_provider = gtk_css_provider_new();
	gtk_css_provider_load_from_path(e->ui->css_provider, "theme/bidou/gtk.css", NULL);
	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(e->ui->css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

	// init the builder and load the template
	e->ui->builder = gtk_builder_new();
	gtk_builder_add_from_file(e->ui->builder, "./theme/rt_ui.glade", NULL);


/////////////////////////////////WIDGET LINKING & INIT//////////////////////////////////
///WE WILL REMOVE ALL UNUSED WIDGET AFTER FINISHING UI DESIGN //////////////////////////

	init_gtk_main_widgets(e);
	init_gtk_scene_widgets(e);

	/////CAMERAS////
	e->ui->cam_frame = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_frame"));
	e->ui->cam_frame_align = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_frame_align"));
	e->ui->cam_frame_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_frame_label"));
	e->ui->cam_frame_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_frame_box"));
	// cam list box
	e->ui->cam_list_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_box"));
	// cam list id
	e->ui->cam_list_id = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_id"));
	e->ui->cam_list_id_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_id_label"));
	ui_cam_set_id(e);
	// cam list pos
	e->ui->cam_list_pos = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_pos"));
	e->ui->cam_list_pos_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_pos_box"));
	e->ui->cam_list_pos_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_pos_label"));
	e->ui->cam_list_pos_spin_x = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_pos_spin_x"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_pos_spin_x, (gdouble)ACTIVECAM.pos.x);
	e->ui->cam_list_pos_spin_y = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_pos_spin_y"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_pos_spin_y, (gdouble)ACTIVECAM.pos.y);
	e->ui->cam_list_pos_spin_z = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_pos_spin_z"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_pos_spin_z, (gdouble)ACTIVECAM.pos.z);
	// cam list dir
	e->ui->cam_list_dir = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_dir"));
	e->ui->cam_list_dir_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_dir_box"));
	e->ui->cam_list_dir_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_dir_label"));
	e->ui->cam_list_dir_spin_x = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_dir_spin_x"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_dir_spin_x, (gdouble)ACTIVECAM.dir.x);
	e->ui->cam_list_dir_spin_y = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_dir_spin_y"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_dir_spin_y, (gdouble)ACTIVECAM.dir.y);
	e->ui->cam_list_dir_spin_z = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_dir_spin_z"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_dir_spin_z, (gdouble)ACTIVECAM.dir.z);
	// cam list fov
	e->ui->cam_list_fov = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_fov"));
	e->ui->cam_list_fov_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_fov_box"));
	e->ui->cam_list_fov_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_fov_label"));
	e->ui->cam_list_fov_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_list_fov_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->cam_list_fov_spin, (guint)ACTIVECAM.fov);
	// cam nav box
	e->ui->cam_nav_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_nav_box"));
	e->ui->cam_nav_prev_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_nav_prev_btn"));
	e->ui->cam_nav_next_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_nav_next_btn"));
	e->ui->cam_nav_add_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_nav_add_btn"));
	e->ui->cam_nav_del_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "cam_nav_del_btn"));
	if (e->scene->n_cams < 2)
	{	
		gtk_widget_set_sensitive(e->ui->cam_nav_prev_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->cam_nav_next_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->cam_nav_del_btn, FALSE);
	}

/////LIGHTS/////

//	printf("selectore = %d\n", e->ui->light_selector);

	e->ui->light_frame = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_frame"));
	e->ui->light_frame_align = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_frame_align"));
	e->ui->light_frame_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_frame_label"));
	e->ui->light_frame_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_frame_box"));
	e->ui->light_list_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_box"));
	//light id
	e->ui->light_list_id = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_id"));
	e->ui->light_list_id_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_id_label"));
	ui_light_set_id(e);
	//light pos
	e->ui->light_list_pos = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos"));
	e->ui->light_list_pos_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_box"));
	e->ui->light_list_pos_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_label"));
	e->ui->light_list_pos_spin_x = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_spin_x"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_x, (gdouble)ACTIVELIGHT.pos.x);
	e->ui->light_list_pos_spin_y = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_spin_y"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_y, (gdouble)ACTIVELIGHT.pos.y);
	e->ui->light_list_pos_spin_z = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_spin_z"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_pos_spin_z, (gdouble)ACTIVELIGHT.pos.z);
	//light params
	e->ui->light_list_params = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_params"));
	e->ui->light_list_params_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_params_box"));
	e->ui->light_list_bright_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_bright_label"));
	e->ui->light_list_bright_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_bright_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_bright_spin, (gdouble)ACTIVELIGHT.brightness);
	e->ui->light_list_shrink_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_shrink_label"));
	e->ui->light_list_shrink_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_shrink_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->light_list_shrink_spin, (gint)ACTIVELIGHT.shrink);
	e->ui->light_list_color_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_color_label"));
	e->ui->light_list_color_button = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_color_button"));
	e->ui->light_color = ui_int_to_gdkrbga((gint)ACTIVELIGHT.color);
	gtk_color_chooser_set_rgba(GTK_COLOR_CHOOSER(e->ui->light_list_color_button), &e->ui->light_color);
	//light nav
	e->ui->light_nav_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_box"));
	e->ui->light_nav_prev_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_prev_btn"));
	e->ui->light_nav_next_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_next_btn"));
	e->ui->light_nav_add_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_add_btn"));
	e->ui->light_nav_del_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_del_btn"));
	if (e->gen_lights->length < 2)
	{	
		gtk_widget_set_sensitive(e->ui->light_nav_prev_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->light_nav_next_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->light_nav_del_btn, FALSE);
	}




////OBJECT////
	e->ui->object_frame = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "object_frame"));
	e->ui->object_frame_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "object_frame_label"));
	e->ui->object_frame_align = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "object_frame_align"));
	e->ui->object_frame_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "object_frame_box"));
	e->ui->obj_list_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_box"));
	//object id
	e->ui->obj_list_id = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_id"));
	e->ui->obj_list_id_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_id_label"));
	
	//object pos
	e->ui->obj_list_pos = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_pos"));
	e->ui->obj_list_pos_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_pos_box"));
	e->ui->obj_list_pos_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_pos_label"));
	e->ui->obj_list_pos_spin_x = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_pos_spin_x"));
	e->ui->obj_list_pos_spin_y = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_pos_spin_y"));
	e->ui->obj_list_pos_spin_z = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_pos_spin_z"));
	//object dir
	e->ui->obj_list_dir = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_dir"));
	e->ui->obj_list_dir_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_dir_box"));
	e->ui->obj_list_dir_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_dir_label"));
	e->ui->obj_list_dir_spin_x = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_dir_spin_x"));
	e->ui->obj_list_dir_spin_y = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_dir_spin_y"));
	e->ui->obj_list_dir_spin_z = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_dir_spin_z"));
	//object diffuse
	e->ui->obj_list_diff = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_diff"));
	e->ui->obj_list_diff_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_diff_box"));
	e->ui->obj_list_diff_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_diff_label"));
	e->ui->obj_list_diff_spin_x = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_diff_spin_x"));
	e->ui->obj_list_diff_spin_y = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_diff_spin_y"));
	e->ui->obj_list_diff_spin_z = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_diff_spin_z"));
	//object specular
	e->ui->obj_list_spec = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_spec"));
	e->ui->obj_list_spec_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_spec_box"));
	e->ui->obj_list_spec_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_spec_label"));
	e->ui->obj_list_spec_spin_x = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_spec_spin_x"));
	e->ui->obj_list_spec_spin_y = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_spec_spin_y"));
	e->ui->obj_list_spec_spin_z = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_spec_spin_z"));
	//object reflex and refract
	e->ui->obj_list_ref = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_ref"));
	e->ui->obj_list_ref_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_ref_box"));
	e->ui->obj_list_reflex_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_reflex_label"));
	e->ui->obj_list_reflex_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_reflex_spin"));
	e->ui->obj_list_refrac_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_refrac_label"));
	e->ui->obj_list_refrac_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_refrac_spin"));
	//object color opacity
	e->ui->obj_list_opacolor = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_opacolor"));
	e->ui->obj_list_opacolor_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_opacolor_box"));
	e->ui->obj_list_opacity_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_opacity_label"));
	e->ui->obj_list_opacity_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_opacity_spin"));

	e->ui->obj_list_color_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_color_label"));
	e->ui->obj_list_color_button = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_list_color_button"));
	//object navigation
	e->ui->obj_nav_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_box"));
	e->ui->obj_nav_first = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_first"));
	e->ui->obj_nav_prev_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_prev_btn"));
	e->ui->obj_nav_next_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_next_btn"));
	e->ui->obj_nav_del_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_del_btn"));	


	e->ui->obj_nav_second = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_second"));
	e->ui->obj_nav_add_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_add_label"));
	e->ui->obj_nav_add_type_combo = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_add_type_combo"));
	e->ui->obj_nav_add_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_add_btn"));
	e->ui->obj_nav_third = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_third"));
	e->ui->obj_nav_jump_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_jump_label"));
	e->ui->obj_nav_jump_combo = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "obj_nav_jump_combo"));
	




////TOOL BAR
	e->ui->tool_bar = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_bar"));
	e->ui->tool_fps_placeholder = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_fps_placeholder"));
	e->ui->tool_fps_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_fps_label"));
	e->ui->tool_play_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_play_btn"));
	e->ui->tool_stop_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_stop_btn"));
	e->ui->tool_render_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_render_btn"));
	e->ui->tool_export_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_export_btn"));
	e->ui->tool_about_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_about_btn"));
	gtk_widget_set_sensitive(e->ui->tool_play_btn, FALSE);
	gtk_widget_set_sensitive(e->ui->tool_render_btn, FALSE);
	gtk_widget_set_sensitive(e->ui->tool_stop_btn, TRUE);

////STATUS BAR
	e->ui->status_bar = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "status_bar"));

////ABOUT DIALOG
e->ui->about_window = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "about_window"));
gtk_window_set_transient_for(GTK_WINDOW(e->ui->about_window), GTK_WINDOW(e->ui->main_window)) ;
/////////////////////////////////////////////////////////////////////////////////////////////
	


/////////////////////////////////SIGNALS AND SHIT/////////////////////////////////////////////
	
	// mainwindow
	g_signal_connect(e->ui->main_window, "destroy", G_CALLBACK(gtk_quit), (gpointer)e);
	g_signal_connect(e->ui->main_window, "check-resize", G_CALLBACK(cb_render_update_size), (gpointer)e);
	
	
	g_signal_connect(e->ui->render,"configure-event", G_CALLBACK(cb_configure_draw_area), (gpointer)e);
	g_signal_connect(e->ui->render, "draw", G_CALLBACK(cb_render_draw), (gpointer)e);
	gtk_widget_add_events (e->ui->render, GDK_BUTTON_PRESS_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "button-press-event", G_CALLBACK(cb_render_btnpress), (gpointer)e);
	gtk_widget_add_events (e->ui->render, GDK_KEY_PRESS_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "key-press-event", G_CALLBACK(cb_render_keypress), (gpointer)e);
	gtk_widget_add_events (e->ui->render, GDK_KEY_RELEASE_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "key-release-event", G_CALLBACK(cb_render_keyrelease), (gpointer)e);
	gtk_widget_grab_focus(e->ui->render);

	//scene resolution spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->scene_resolution_width_spin), "value-changed", G_CALLBACK(cb_res_width_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_resolution_height_spin), "value-changed", G_CALLBACK(cb_res_height_update), (gpointer)e);
	//scene ambient spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_red_spin), "value-changed", G_CALLBACK(cb_ambient_red_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_green_spin), "value-changed", G_CALLBACK(cb_ambient_green_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_blue_spin), "value-changed", G_CALLBACK(cb_ambient_blue_update), (gpointer)e);
	//scene depth spinbutton
	g_signal_connect(GTK_WIDGET(e->ui->scene_depth_spin), "value-changed", G_CALLBACK(cb_depth_update), (gpointer)e);
	//scene supersampling scale
	g_signal_connect(GTK_WIDGET(e->ui->scene_supersampling_scale), "value-changed", G_CALLBACK(cb_supersampling_update), (gpointer)e);
	//scene postproc radiobuttons
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_none_radio), "toggled", G_CALLBACK(cb_postproc_none), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_bw_radio), "toggled", G_CALLBACK(cb_postproc_bw), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_sepia_radio), "toggled", G_CALLBACK(cb_postproc_sepia), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_invert_check), "toggled", G_CALLBACK(cb_postproc_invert), (gpointer)e);
	//cam pos spinbutton
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_pos_spin_x), "value-changed", G_CALLBACK(cb_cam_pos_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_pos_spin_y), "value-changed", G_CALLBACK(cb_cam_pos_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_pos_spin_z), "value-changed", G_CALLBACK(cb_cam_pos_z), (gpointer)e);
	//cam fov spinbutton
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_fov_spin), "value-changed", G_CALLBACK(cb_cam_fov_update), (gpointer)e);
	//cam nav buttons
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_prev_btn), "clicked", G_CALLBACK(cb_cam_nav_prev), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_next_btn), "clicked", G_CALLBACK(cb_cam_nav_next), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_add_btn), "clicked", G_CALLBACK(cb_cam_manage_add), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_del_btn), "clicked", G_CALLBACK(cb_cam_manage_del), (gpointer)e);
	//light pos spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->light_list_pos_spin_x), "value-changed", G_CALLBACK(cb_light_pos_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_list_pos_spin_y), "value-changed", G_CALLBACK(cb_light_pos_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_list_pos_spin_z), "value-changed", G_CALLBACK(cb_light_pos_z), (gpointer)e);
	//light param buttons
	g_signal_connect(GTK_WIDGET(e->ui->light_list_bright_spin), "value-changed", G_CALLBACK(cb_light_brightness), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_list_shrink_spin), "value-changed", G_CALLBACK(cb_light_shrink), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_list_color_button), "color-set", G_CALLBACK(cb_light_color), (gpointer)e);
	//light nav buttons
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_prev_btn), "clicked", G_CALLBACK(cb_light_nav_prev), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_next_btn), "clicked", G_CALLBACK(cb_light_nav_next), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_add_btn), "clicked", G_CALLBACK(cb_light_manage_add), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_del_btn), "clicked", G_CALLBACK(cb_light_manage_del), (gpointer)e);
	
	
	//objects
	// obj pos spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_pos_spin_x), "value-changed", G_CALLBACK(cb_obj_pos_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_pos_spin_y), "value-changed", G_CALLBACK(cb_obj_pos_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_pos_spin_z), "value-changed", G_CALLBACK(cb_obj_pos_z), (gpointer)e);
	// obj dir spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_dir_spin_x), "value-changed", G_CALLBACK(cb_obj_dir_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_dir_spin_y), "value-changed", G_CALLBACK(cb_obj_dir_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_dir_spin_z), "value-changed", G_CALLBACK(cb_obj_dir_z), (gpointer)e);
	// obj diff spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_diff_spin_x), "value-changed", G_CALLBACK(cb_obj_diff_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_diff_spin_y), "value-changed", G_CALLBACK(cb_obj_diff_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_diff_spin_z), "value-changed", G_CALLBACK(cb_obj_diff_z), (gpointer)e);
	// obj spec spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_spec_spin_x), "value-changed", G_CALLBACK(cb_obj_spec_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_spec_spin_y), "value-changed", G_CALLBACK(cb_obj_spec_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_spec_spin_z), "value-changed", G_CALLBACK(cb_obj_spec_z), (gpointer)e);
	// obj ref spinbutton
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_reflex_spin), "value-changed", G_CALLBACK(cb_obj_reflex), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_refrac_spin), "value-changed", G_CALLBACK(cb_obj_refrac), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_opacity_spin), "value-changed", G_CALLBACK(cb_obj_opacity), (gpointer)e);
	// obj colorbutton
	g_signal_connect(GTK_WIDGET(e->ui->obj_list_color_button), "color-set", G_CALLBACK(cb_obj_color), (gpointer)e);
	// obj nav buttons
	g_signal_connect(GTK_WIDGET(e->ui->obj_nav_prev_btn), "clicked", G_CALLBACK(cb_obj_nav_prev), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->obj_nav_next_btn), "clicked", G_CALLBACK(cb_obj_nav_next), (gpointer)e);


	//tool bar buttons
	g_signal_connect(GTK_WIDGET(e->ui->tool_play_btn), "clicked", G_CALLBACK(cb_play_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_stop_btn), "clicked", G_CALLBACK(cb_stop_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_render_btn), "clicked", G_CALLBACK(cb_render_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_export_btn), "clicked", G_CALLBACK(cb_export_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_about_btn), "clicked", G_CALLBACK(cb_about_btn), (gpointer)e);
	// init and activate all preset signals from template
	gtk_builder_connect_signals(e->ui->builder, NULL);
/////////////////////////////////////////////////////////////////////////////////////////////

	
	// free the builder
	g_object_unref(e->ui->builder);
	gtk_widget_show_all(e->ui->main_window);

	// init obj manager hiding shit
	ui_obj_set_id(e, e->gen_objects->mem + e->target);
//	gtk_widget_hide(e->ui->obj_list_box);
//	gtk_widget_hide(e->ui->obj_nav_prev_btn);
//	gtk_widget_hide(e->ui->obj_nav_next_btn);
//	gtk_widget_hide(e->ui->obj_nav_del_btn);

	g_idle_add(gtk_main_loop, (gpointer)e);
	gtk_main();
}
