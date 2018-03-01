#include "rt.h"

void		*construct_gen()
{
	t_gen *gen;

	if (!(gen = ft_memalloc(sizeof(t_gen))))
		return (NULL);
	gen->add = &gen_add;
	return (gen);
}
