#include "rt.h"

void		print_obj(t_gen *gen, void *data)
{
	t_object *obj;

	(void)gen;
	obj = (t_object *)data;
	printf("TYPE	[%i]\n", obj->type);
	printf("ID		[%i]\n", obj->id);
	printf("pos		[%.2f %.2f %.2f]\n", obj->pos.x, obj->pos.y, obj->pos.z);
	printf("dir		[%.2f %.2f %.2f]\n", obj->dir.x, obj->dir.y, obj->dir.z);
	if (obj->type == OBJ_BOX)
	{
		printf("min		[%.2f %.2f %.2f]\n", ((t_box *)obj)->min.x, \
								((t_box *)obj)->min.y, ((t_box *)obj)->min.z);
		printf("max		[%.2f %.2f %.2f]\n", ((t_box *)obj)->max.x, \
								((t_box *)obj)->max.y, ((t_box *)obj)->max.z);
	}
}
