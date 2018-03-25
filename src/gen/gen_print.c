#include "gen.h"

void		gen_print(t_gen *gen, void (*print)(t_gen *, void *))
{
	size_t			mem_index;

	mem_index = 0;
	ft_putstr("PRINT_GEN:\n");
	while (mem_index < gen->mem_size)
	{
		ft_putstr("Obj: ");
		ft_putnbr((int)mem_index);
		ft_putstr("/");
		ft_putnbr((int)gen->mem_size);
		ft_putstr("\n");
		print(gen, (gen->mem + mem_index));
		mem_index += *((int *)(gen->mem + mem_index));
	}
	ft_putchar('\n');
}
