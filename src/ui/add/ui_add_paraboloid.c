#include "rt.h"

void	ui_add_paraboloid(t_env *e)
{
	t_paraboloid paraboloid;

	paraboloid.size = sizeof(t_paraboloid);
	paraboloid.id = e->gen_objects->length;
	paraboloid.type = OBJ_PARABOLOID;
	paraboloid.pos.x = 0;
	paraboloid.pos.y = 0;
	paraboloid.pos.z = 0;
	paraboloid.dir.x = 0;
	paraboloid.dir.y = 0;
	paraboloid.dir.z = 1;
	paraboloid.dir = normalize_vect(paraboloid.dir);
	paraboloid.base_dir.x = 0;
	paraboloid.base_dir.y = 0;
	paraboloid.base_dir.z = 1;
	paraboloid.base_dir = normalize_vect(paraboloid.dir);
	paraboloid.radius = 4;
	paraboloid.color = rand();
	paraboloid.height = 2;
	paraboloid.diff.x = 0.42;
	paraboloid.diff.y = 0.42;
	paraboloid.diff.z = 0.42;
	paraboloid.spec.x = 0.42;
	paraboloid.spec.y = 0.42;
	paraboloid.spec.z = 0.42;
	paraboloid.reflex = 0;
	paraboloid.refract = 0;
	paraboloid.opacity = 1;
	e->gen_objects->add(e->gen_objects, (void*)&paraboloid);
}
