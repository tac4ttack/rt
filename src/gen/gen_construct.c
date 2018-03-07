#include "rt.h"

void		*gen_construct()
{
	t_gen *gen;

	if (!(gen = ft_memalloc(sizeof(t_gen))))
		return (NULL);
	gen->add = &gen_add;
	return (gen);
}
