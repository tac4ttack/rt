#include "rt.h"

void		cb_about_btn(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	ft_putendl("abouteu");
	gtk_dialog_run(GTK_DIALOG(e->ui->about_window));
	gtk_widget_destroy(e->ui->about_window);
	t_gen *gen = e->gen_objects;
	gen->remove_mem_index(gen, *((int*)gen->mem));
	gen->print(gen, &print_obj);
}
