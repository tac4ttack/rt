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
	printf("key is %d\n", key);
	(key == KEY_UA ? KEY_STATE_UA = 1 : 0 );
	(key == KEY_DA ? KEY_STATE_DA = 1 : 0 );
	(key == KEY_LA ? KEY_STATE_LA = 1 : 0 );
	(key == KEY_RA ? KEY_STATE_RA = 1 : 0 );
	(key == KEY_ESC ? KEY_STATE_ESC = 1 : 0 );
	(key == KEY_SPC ? KEY_STATE_SPC = 1 : 0 );
	(key == KEY_NPLU ? KEY_STATE_NPLU = 1 : 0 );
	(key == KEY_NMIN ? KEY_STATE_NMIN = 1 : 0 );
	(key == KEY_N4 ? KEY_STATE_N4 = 1 : 0 );
	(key == KEY_N5 ? KEY_STATE_N5 = 1 : 0 );
	(key == KEY_N6 ? KEY_STATE_N6 = 1 : 0 );
	(key == KEY_N7 ? KEY_STATE_N7 = 1 : 0 );
	(key == KEY_N8 ? KEY_STATE_N8 = 1 : 0 );
	(key == KEY_N9 ? KEY_STATE_N9 = 1 : 0 );
	(key == KEY_W ? KEY_STATE_W = 1 : 0 );
	(key == KEY_A ? KEY_STATE_A = 1 : 0 );
	(key == KEY_S ? KEY_STATE_S = 1 : 0 );
	(key == KEY_D ? KEY_STATE_D = 1 : 0 );
	(key == KEY_C ? KEY_STATE_C = 1 : 0 );
	(key == KEY_I ? KEY_STATE_I = 1 : 0 );
	(key == KEY_J ? KEY_STATE_J = 1 : 0 );
	(key == KEY_K ? KEY_STATE_K = 1 : 0 );
	(key == KEY_L ? KEY_STATE_L = 1 : 0 );
	(key == KEY_U ? KEY_STATE_U = 1 : 0 );
	(key == KEY_O ? KEY_STATE_O = 1 : 0 );
	(key == KEY_Z ? KEY_STATE_Z = 1 : 0 );
	
	return TRUE;
}
