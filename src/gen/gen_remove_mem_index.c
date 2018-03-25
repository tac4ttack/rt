#include "gen.h"

static bool	gen_remove_mem_index_0(t_gen *gen, const int current_mem_size)
{
	void			*tmp;

	gen->mem_size -= current_mem_size;
	tmp = gen->mem;
	if (!gen->unit_size)
		gen->mem = NULL;
	else
		gen->mem = ft_memnew(gen->mem + current_mem_size, gen->mem_size);
	gen->unit_size--;
	if (tmp)
		ft_memdel((void**)&tmp);
	if (!gen->mem)
		return (false);
	return (true);
}

static bool	gen_remove_mem_index_other(t_gen *gen,
										const int current_mem_size,
										const size_t mem_index)
{
	void			*tmp;

	gen->mem_size -= current_mem_size;
	gen->unit_size--;
	tmp = gen->mem;
	if (!(gen->mem = ft_memalloc(gen->mem_size)))
	{
		gen->mem = tmp;
		return (false);
	}
	ft_memcpy(gen->mem, tmp, mem_index);
	ft_memcpy(gen->mem + mem_index,
				tmp + mem_index + current_mem_size,
				gen->mem_size - mem_index);
	return (true);
}

bool		gen_remove_mem_index(t_gen *gen, size_t mem_remove_index)
{
	size_t			mem_index;
	int				*current_mem_size;

	if (mem_remove_index > gen->mem_size)
		return (false);
	current_mem_size = gen->mem;
	if (!mem_remove_index)
		return (gen_remove_mem_index_0(gen, *current_mem_size));
	mem_index = 0;
	while (mem_index < gen->mem_size)
	{
		if (mem_index == mem_remove_index)
		{
			return (gen_remove_mem_index_other(gen,
											*current_mem_size, mem_index));
		}
		current_mem_size = (int *)(gen->mem + mem_index);
		mem_index += *current_mem_size;
	}
	return (false);
}
