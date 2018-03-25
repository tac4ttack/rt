#include "gen.h"

bool		gen_add(t_gen *gen, void *elem)
{
	int size;

	size = *((int *)elem);
	if (!(gen->mem = ft_memrealloc(gen->mem, gen->mem_size, gen->mem_size + size)))
		return (false);
	ft_memcpy(gen->mem + gen->mem_size, elem, size);
	gen->mem_size += size;
	gen->unit_size++;
	return (true);
}
