#include "rt.h"

void		print_obj(t_gen *gen, void *data)
{
	t_object *obj;

	(void)gen;
	obj = (t_object *)data;
	printf("TYPE	[%i]\n", obj->type);
	printf("ID		[%i]\n", obj->id);
	printf("pos		[%.2f %.2f %.2f]\n", obj->pos.x, obj->pos.y, obj->pos.z);
}

void		cb_about_btn(GtkButton *btn, gpointer data)
{
	t_env	*e;

	(void)btn;
	e = data;
	ft_putendl("abouteu");
	gtk_dialog_run(GTK_DIALOG(e->ui->about_window));
	gtk_widget_destroy(e->ui->about_window);
	t_gen *gen = e->gen_objects;
	gen->remove_mem_index(gen, 0);
	gen->print(gen, &print_obj);
	//exit(0);
}
