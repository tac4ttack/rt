#include "gen.h"

void		*gen_get_index(t_gen *gen, int index)
{
	size_t			mem_index;
	int				current_index;
	int				*current_mem_size;

	mem_index = 0;
	current_index = 0;
	while (mem_index < gen->mem_size)
	{
		if (index == current_index)
			return (gen->mem + mem_index);
		current_mem_size = (int *)(gen->mem + mem_index);
		mem_index += *current_mem_size;
		current_index++;
	}
	return (NULL);
}
