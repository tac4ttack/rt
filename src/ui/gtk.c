#include "rt.h"

void		init_gtk_main_widgets(t_env *e)
{
	////MAIN WINDOW
	// init and connect the main window
	e->ui->main_window = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_window"));

////MAIN PANEL	
	// init all widget in order
	e->ui->main_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_box"));
	e->ui->main_panels = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "main_panels"));

////LEFT PANEL
	e->ui->left_panel_scroll = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "left_panel_scroll"));
	e->ui->left_panel_viewport = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "left_panel_viewport"));
	// init render shit
	e->ui->render = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "render"));
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
	// scene depth shit
	e->ui->scene_depth_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_depth_box"));
	e->ui->scene_depth_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_depth_label"));
	e->ui->scene_depth_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "scene_depth_spin"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->scene_depth_spin, (gdouble)e->scene->depth);
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

////CSS STYLING
//	e->ui->css_provider = gtk_css_provider_new();
//	gtk_css_provider_load_from_path(e->ui->css_provider, "./theme/gtk-dark.css", NULL);
//	gtk_style_context_add_provider_for_screen(gdk_screen_get_default(), GTK_STYLE_PROVIDER(e->ui->css_provider), GTK_STYLE_PROVIDER_PRIORITY_USER);

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
	gtk_label_set_text(GTK_LABEL(e->ui->cam_list_id_label), "CAMERA #1");
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
	ui_cam_set_id(e);
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
	printf("selectore = %d\n", e->ui->light_selector);
	e->ui->light_frame = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_frame"));
	e->ui->light_frame_align = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_frame_align"));
	e->ui->light_frame_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_frame_label"));
	e->ui->light_frame_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_frame_box"));
	e->ui->light_list_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_box"));
	//light id
	e->ui->light_list_id = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_id"));
	e->ui->light_list_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_label"));
	//light pos
	e->ui->light_list_pos = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos"));
	e->ui->light_list_pos_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_box"));
	e->ui->light_list_pos_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_label"));
	e->ui->light_list_pos_spin_x = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_spin_x"));
	e->ui->light_list_pos_spin_y = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_spin_y"));
	e->ui->light_list_pos_spin_z = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_pos_spin_z"));
	//light params
	e->ui->light_list_params = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_params"));
	e->ui->light_list_params_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_params_box"));
	e->ui->light_list_bright_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_bright_label"));
	e->ui->light_list_bright_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_bright_spin"));
	e->ui->light_list_shrink_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_shrink_label"));
	e->ui->light_list_shrink_spin = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_shrink_spin"));
	e->ui->light_list_color_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_color_label"));
	e->ui->light_list_color_button = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_list_color_button"));
	//light nav
	e->ui->light_nav_box = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_box"));
	e->ui->light_nav_prev_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_prev_btn"));
	e->ui->light_nav_next_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_next_btn"));
	e->ui->light_nav_add_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_add_btn"));
	e->ui->light_nav_del_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "light_nav_del_btn"));
	if (e->scene->n_lights < 2)
	{	
		gtk_widget_set_sensitive(e->ui->light_nav_prev_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->light_nav_next_btn, FALSE);
		gtk_widget_set_sensitive(e->ui->light_nav_del_btn, FALSE);
	}

////TOOL BAR
	e->ui->tool_bar = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_bar"));
	e->ui->tool_play_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_play_btn"));
	e->ui->tool_stop_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_stop_btn"));
	e->ui->tool_export_btn = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_export_btn"));
	e->ui->tool_separate = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_separate"));
	e->ui->tool_fps_placeholder = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_fps_placeholder"));
	e->ui->tool_fps_label = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_fps_label"));


////STATUS BAR
	e->ui->status_bar = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "status_bar"));


/////////////////////////////////////////////////////////////////////////////////////////////
	


/////////////////////////////////SIGNALS AND SHIT/////////////////////////////////////////////
	
	// mainwindow
	g_signal_connect(e->ui->main_window, "destroy", G_CALLBACK(gtk_quit), (gpointer)e);

	// render
	g_signal_connect(e->ui->render,"configure-event", G_CALLBACK(cb_configure_draw_area), (gpointer)e);
	g_signal_connect(e->ui->render, "draw", G_CALLBACK(cb_draw_render), (gpointer)e);
	gtk_widget_add_events (e->ui->render, GDK_BUTTON_PRESS_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "button-press-event", G_CALLBACK(cb_render_btnpress), (gpointer)e);
	gtk_widget_add_events (e->ui->render, GDK_KEY_PRESS_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "key-press-event", G_CALLBACK(cb_render_keypress), (gpointer)e);
	gtk_widget_add_events (e->ui->render, GDK_KEY_RELEASE_MASK);
	g_signal_connect(GTK_WIDGET(e->ui->render), "key-release-event", G_CALLBACK(cb_render_keyrelease), (gpointer)e);
	gtk_widget_grab_focus(e->ui->render);

	//scene resolution spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->scene_resolution_width_spin), "value-changed", G_CALLBACK(cb_width_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_resolution_height_spin), "value-changed", G_CALLBACK(cb_height_update), (gpointer)e);
	//scene ambient spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_red_spin), "value-changed", G_CALLBACK(cb_ambient_red_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_green_spin), "value-changed", G_CALLBACK(cb_ambient_green_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_blue_spin), "value-changed", G_CALLBACK(cb_ambient_blue_update), (gpointer)e);
	//scene depth spinbutton
	g_signal_connect(GTK_WIDGET(e->ui->scene_depth_spin), "value-changed", G_CALLBACK(cb_depth_update), (gpointer)e);
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
	g_signal_connect(GTK_WIDGET(e->ui->cam_list_fov_spin), "value-changed", G_CALLBACK(cb_camfov_update), (gpointer)e);
	//cam nav buttons
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_prev_btn), "clicked", G_CALLBACK(cb_cam_nav_prev), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_next_btn), "clicked", G_CALLBACK(cb_cam_nav_next), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_add_btn), "clicked", G_CALLBACK(cb_cam_manage_add), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->cam_nav_del_btn), "clicked", G_CALLBACK(cb_cam_manage_del), (gpointer)e);
	//light nav buttons
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_prev_btn), "clicked", G_CALLBACK(cb_light_nav_prev), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_next_btn), "clicked", G_CALLBACK(cb_light_nav_next), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_add_btn), "clicked", G_CALLBACK(cb_light_manage_add), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->light_nav_del_btn), "clicked", G_CALLBACK(cb_light_manage_del), (gpointer)e);
	//tool bar buttons
	g_signal_connect(GTK_WIDGET(e->ui->tool_play_btn), "clicked", G_CALLBACK(cb_play_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_stop_btn), "clicked", G_CALLBACK(cb_stop_btn), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->tool_export_btn), "clicked", G_CALLBACK(cb_export_btn), (gpointer)e);
	// init and activate all preset signals from template
	gtk_builder_connect_signals(e->ui->builder, NULL);
/////////////////////////////////////////////////////////////////////////////////////////////

	

	// free the builder
	g_object_unref(e->ui->builder);
	gtk_widget_show_all(e->ui->main_window);
	g_idle_add(gtk_main_loop, (gpointer)e);
	gtk_main();
}
