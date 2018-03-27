#include "rt.h"

void	ui_add_cylinder(t_env *e)
{
	t_cylinder cylinder;

	cylinder.size = sizeof(t_cylinder);
	cylinder.id = e->gen_objects->length;
	cylinder.type = OBJ_CYLINDER;
	cylinder.pos.x = 0;
	cylinder.pos.y = 0;
	cylinder.pos.z = 0;
	cylinder.dir.x = 0;
	cylinder.dir.y = 0;
	cylinder.dir.z = 1;
	cylinder.dir = normalize_vect(cylinder.dir);
	cylinder.base_dir.x = 0;
	cylinder.base_dir.y = 0;
	cylinder.base_dir.z = 1;
	cylinder.base_dir = normalize_vect(cylinder.dir);
	cylinder.radius = 4;
	cylinder.color = rand();
	cylinder.height = 0;
	cylinder.diff.x = 0.42;
	cylinder.diff.y = 0.42;
	cylinder.diff.z = 0.42;
	cylinder.spec.x = 0.42;
	cylinder.spec.y = 0.42;
	cylinder.spec.z = 0.42;
	cylinder.reflex = 0;
	cylinder.refract = 0;
	cylinder.opacity = 1;
	e->gen_objects->add(e->gen_objects, (void*)&cylinder);
}
