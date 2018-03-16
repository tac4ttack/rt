#include "rt.h"

void		cb_postproc_none(GtkToggleButton *button, gpointer data)
{
	t_env *e;
	
	(void)button;
	e = data;
	e->scene->flag ^= OPTION_BW;
	e->scene->flag ^= OPTION_SEPIA;
}

void		cb_postproc_sepia(GtkToggleButton *button, gpointer data)
{
	t_env *e;
	
	(void)button;
	e = data;
	e->scene->flag ^= OPTION_BW;
	e->scene->flag |= OPTION_SEPIA;
}

void		cb_postproc_bw(GtkToggleButton *button, gpointer data)
{
	t_env *e;
	
	(void)button;
	e = data;
	e->scene->flag |= OPTION_BW;
	e->scene->flag ^= OPTION_SEPIA;
}
