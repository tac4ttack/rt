#include "gen.h"

void		*gen_construct()
{
	t_gen *gen;

	if (!(gen = ft_memalloc(sizeof(t_gen))))
		return (NULL);
	gen->add = &gen_add;
	gen->remove_mem_index = &gen_remove_mem_index;
	gen->remove_index = &gen_remove_index;
	gen->print = &gen_print;
	return (gen);
}
