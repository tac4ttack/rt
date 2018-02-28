#include "rt.h"

void mlx_key_no_repeat_event(t_env *e, const int key)
{
	if (key == K_1)
	{
		if (e->scene->flag & OPTION_WAVE)
			e->scene->flag ^= OPTION_WAVE;
		else
			e->scene->flag |= OPTION_WAVE;
	}
	if (key == K_2)
	{
		if (e->scene->flag & OPTION_BW)
			e->scene->flag ^= OPTION_BW;
		if (e->scene->flag & OPTION_SEPIA)
			e->scene->flag ^= OPTION_SEPIA;
		else
			e->scene->flag |= OPTION_SEPIA;
	}
	if (key == K_3)
	{
		if (e->scene->flag & OPTION_SEPIA)
			e->scene->flag ^= OPTION_SEPIA;
		if (e->scene->flag & OPTION_BW)
			e->scene->flag ^= OPTION_BW;
		else
			e->scene->flag |= OPTION_BW;
	}
}
