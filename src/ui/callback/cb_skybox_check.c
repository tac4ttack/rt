#include "rt.h"

void	cb_skybox_check(GtkToggleButton *button, gpointer data)
{
	t_env *e;

	(void)button;
	e = data;
	if (e->scene->flag & OPTION_SKYBOX)
		e->scene->flag ^= OPTION_SKYBOX;
	else
		e->scene->flag |= OPTION_SKYBOX;
}
