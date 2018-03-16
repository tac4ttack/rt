#include "rt.h"

void	gtk_render_events(t_env *e)
{
	if (KEY_STATE_NPLU || KEY_STATE_NMIN)
	{
		if (KEY_STATE_NPLU)
			e->scene->depth++;
		if (KEY_STATE_NMIN)
		{
			(e->scene->depth > 0 ? e->scene->depth-- : 0);
			e->scene->tor_count = pow(2, e->scene->depth + 1) - 1;
		}
		opencl_set_args(e, e->cl);
	}
	if (KEY_STATE_I || KEY_STATE_J || KEY_STATE_K || KEY_STATE_L || \
		KEY_STATE_O || KEY_STATE_N4 || KEY_STATE_N6 || KEY_STATE_N8 \
		|| KEY_STATE_N5 || KEY_STATE_N7 || KEY_STATE_N9)
		ui_obj(e);
	if (KEY_STATE_W || KEY_STATE_S || KEY_STATE_C || KEY_STATE_A || \
		KEY_STATE_D || KEY_STATE_SPC || KEY_STATE_Z || KEY_STATE_UA || \
		KEY_STATE_DA || KEY_STATE_LA || KEY_STATE_RA)
		ui_cam(e);	
}
