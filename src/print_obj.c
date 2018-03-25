#include "rt.h"

void		print_obj(t_gen *gen, void *data)
{
	t_object *obj;

	(void)gen;
	obj = (t_object *)data;
	printf("TYPE	[%i]\n", obj->type);
	printf("ID		[%i]\n", obj->id);
	printf("pos		[%.2f %.2f %.2f]\n", obj->pos.x, obj->pos.y, obj->pos.z);
}
