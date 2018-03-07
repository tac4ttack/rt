#include "rt.h"

void		*destruct_gen(t_gen **gen)
{
	if ((*gen)->mem)
		free((*gen)->mem);
	ft_memdel((void **)gen);
	return (NULL);
}
