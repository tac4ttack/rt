#include "rt.h"

gboolean cb_render_keypress(GtkWidget *widget, GdkEvent *event, gpointer data)
{
	t_env *e;
	guint key;

	(void)widget;
	e = data;
	if (!e)
		exit(EXIT_FAILURE);
	key = event->key.keyval;
	if (key == GDK_KEY_plus)
		e->scene->depth++;
	if (key == GDK_KEY_minus)
	{
		(e->scene->depth > 0 ? e->scene->depth-- : 0);
		e->scene->tor_count = pow(2, e->scene->depth + 1) - 1;
	}
	
	printf("key is %d\n", (int)key);

	if (key == GDK_KEY_I || key == GDK_KEY_J || key == GDK_KEY_K || \
		key == GDK_KEY_L || key == GDK_KEY_O || key == GDK_KEY_KP_4 || \
		key == GDK_KEY_KP_6 || key == GDK_KEY_KP_8 || key == GDK_KEY_KP_5 || \
		key == GDK_KEY_KP_7 || key == GDK_KEY_KP_9)
		ui_obj(e, key);
	
	if (key == GDK_KEY_W || key == GDK_KEY_S || key == GDK_KEY_C || \
		key == GDK_KEY_A || key == GDK_KEY_D || key == GDK_KEY_space || key == GDK_KEY_Z || \
		key == 65362 || key == GDK_KEY_downarrow || \
		key == GDK_KEY_leftarrow || key == GDK_KEY_rightarrow)
		ui_cam(e, key);

opencl_set_args(e, e->cl);
	ft_putendl("test keypress 1");
	return TRUE;
}
