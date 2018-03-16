#include "rt.h"

void		init_gtk(GtkApplication* app, gpointer data)
{
	t_env *e;

	e = data;
	(void)app;
	ft_bzero(&e->ui->keys, sizeof(t_keystate));

//	// css loading
//	e->ui->css = gtk_css_provider_new();
//	gtk_css_provider_load_from_path(e->ui->css, "./theme/gtk-dark.css", NULL);

	// init the builder and load the template
	e->ui->builder = gtk_builder_new();
	gtk_builder_add_from_file(e->ui->builder, "./theme/rt_ui.glade", NULL);


/////////////////////////////////WIDGET LINKING & INIT//////////////////////////////////
///WE WILL REMOVE ALL UNUSED WIDGET AFTER FINISHING UI DESIGN //////////////////////////

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

////TOOL BAR
	e->ui->tool_bar = GTK_WIDGET(gtk_builder_get_object(e->ui->builder, "tool_bar"));

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

	//scene depth spinbutton
	g_signal_connect(GTK_WIDGET(e->ui->scene_depth_spin), "value-changed", G_CALLBACK(cb_depth_update), (gpointer)e);
	//scene ambient spinbuttons
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_red_spin), "value-changed", G_CALLBACK(cb_ambient_red_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_green_spin), "value-changed", G_CALLBACK(cb_ambient_green_update), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_ambient_blue_spin), "value-changed", G_CALLBACK(cb_ambient_blue_update), (gpointer)e);
	//scene postproc radiobuttons
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_none_radio), "toggled", G_CALLBACK(cb_postproc_none), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_bw_radio), "toggled", G_CALLBACK(cb_postproc_bw), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->scene_postproc_sepia_radio), "toggled", G_CALLBACK(cb_postproc_sepia), (gpointer)e);
	// init and activate all preset signals from template
	gtk_builder_connect_signals(e->ui->builder, NULL);
/////////////////////////////////////////////////////////////////////////////////////////////


	// free the builder
	g_object_unref(e->ui->builder);
	gtk_widget_show_all(e->ui->main_window);
	g_idle_add(gtk_main_loop, (gpointer)e);
	gtk_main();
}
