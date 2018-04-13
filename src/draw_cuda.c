#include "rt.h"

#	ifdef DCUDA

int				draw(t_env *e)
{
	render_cuda(&e->cuda, e->pixel_data,
					e->gen_objects,
					e->gen_lights,
					e->fps.u_time,
					e->scene,
					e->cameras);
 	return (0);
}

#	endif
