#include "rt.h"

void		init_kernel(t_env *e)
{
	init_cuda2(&e->cuda, e->scene, e->gen_objects, e->gen_lights, e->texture);
}
