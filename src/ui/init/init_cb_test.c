#include "rt.h"

void					init_test_var_cb(t_env *e)
{
	g_signal_connect(GTK_WIDGET(e->ui->test1_var1_spin_x), \
	"value-changed", G_CALLBACK(cb_test_var1_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->test1_var1_spin_y), \
	"value-changed", G_CALLBACK(cb_test_var1_y), (gpointer)e);

	g_signal_connect(GTK_WIDGET(e->ui->test2_var2_spin_x), \
	"value-changed", G_CALLBACK(cb_test_var2_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->test2_var2_spin_y), \
	"value-changed", G_CALLBACK(cb_test_var2_y), (gpointer)e);

	g_signal_connect(GTK_WIDGET(e->ui->test3_var3_spin_x), \
	"value-changed", G_CALLBACK(cb_test_var3_x), (gpointer)e);
	g_signal_connect(GTK_WIDGET(e->ui->test3_var3_spin_y), \
	"value-changed", G_CALLBACK(cb_test_var3_y), (gpointer)e);
}
