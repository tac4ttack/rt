#include "rt.h"

static void	init_cb_texture(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->texture_wave_par1_spin_x),\
	"value-changed", G_CALLBACK(cb_waves_p1_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->texture_wave_par1_spin_y),\
	"value-changed", G_CALLBACK(cb_waves_p1_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->texture_wave_par1_spin_z),\
	"value-changed", G_CALLBACK(cb_waves_p1_z), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->texture_wave_par2_spin_x),\
	"value-changed", G_CALLBACK(cb_waves_p2_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->texture_wave_par2_spin_y),\
	"value-changed", G_CALLBACK(cb_waves_p2_y), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->texture_wave_par2_spin_z),\
	"value-changed", G_CALLBACK(cb_waves_p2_z), (gpointer)e);
}

void		init_gtk_texture(t_env *e)
{
	e->ui->texture_wave_par1_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "texture_wave_par1_spin_x"));
	e->ui->texture_wave_par1_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "texture_wave_par1_spin_y"));
	e->ui->texture_wave_par1_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "texture_wave_par1_spin_z"));
	e->ui->texture_wave_par2_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "texture_wave_par2_spin_x"));
	e->ui->texture_wave_par2_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "texture_wave_par2_spin_y"));
	e->ui->texture_wave_par2_spin_z = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "texture_wave_par2_spin_z"));
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->texture_wave_par1_spin_x,\
	(gdouble)e->scene->waves_p1.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->texture_wave_par1_spin_y,\
	(gdouble)e->scene->waves_p1.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->texture_wave_par1_spin_z,\
	(gdouble)e->scene->waves_p1.z);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->texture_wave_par2_spin_x,\
	(gdouble)e->scene->waves_p2.x);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->texture_wave_par2_spin_y,\
	(gdouble)e->scene->waves_p2.y);
	gtk_spin_button_set_value((GtkSpinButton*)e->ui->texture_wave_par2_spin_z,\
	(gdouble)e->scene->waves_p2.z);
	init_cb_texture(e);
}
