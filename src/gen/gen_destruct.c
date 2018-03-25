#include "gen.h"

void		*gen_destruct(t_gen **gen)
{
	if ((*gen)->mem)
		free((*gen)->mem);
	ft_memdel((void **)gen);
	return (NULL);
}
