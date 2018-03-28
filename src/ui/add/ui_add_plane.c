#include "rt.h"

void	ui_add_plane(t_env *e)
{
	t_plane plane;

	plane.size = sizeof(t_plane);
	plane.id = e->gen_objects->length;
	plane.type = OBJ_PLANE;
	plane.pos.x = 0;
	plane.pos.y = 0;
	plane.pos.z = 0;
	plane.normal.x = 0;
	plane.normal.y = 0;
	plane.normal.z = 1;
	plane.color = rand();
	plane.diff.x = 0.42;
	plane.diff.y = 0.42;
	plane.diff.z = 0.42;
	plane.spec.x = 0.42;
	plane.spec.y = 0.42;
	plane.spec.z = 0.42;
	plane.reflex = 0;
	plane.refract = 0;
	plane.opacity = 1;
	e->gen_objects->add(e->gen_objects, (void*)&plane);
}
