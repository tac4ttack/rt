#include "rt.h"

void	init_test_var(t_env *e)
{
	e->ui->test1_var1_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "test1_var1_spin_x"));
	e->ui->test1_var1_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "test1_var1_spin_y"));

	e->ui->test2_var2_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "test2_var2_spin_x"));
	e->ui->test2_var2_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "test2_var2_spin_y"));

	e->ui->test3_var3_spin_x = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "test3_var3_spin_x"));
	e->ui->test3_var3_spin_y = GTK_WIDGET(gtk_builder_get_object(\
	e->ui->builder, "test3_var3_spin_y"));
}
