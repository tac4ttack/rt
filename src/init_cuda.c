#include "rt.h"

#	ifdef DCUDA
	void		init_kernel(t_env *e)
	{
		init_cuda(&e->cuda, e->scene, e->gen_objects, e->gen_lights, e->texture);
	}
#	endif
