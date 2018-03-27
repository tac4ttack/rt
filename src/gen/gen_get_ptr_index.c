#include "gen.h"

int			gen_get_ptr_index(t_gen *gen, void *obj)
{
	void	*tmp;
	int		res;

	tmp = obj;
	res = 0;
	if (obj == gen->mem)
		return (res);
	else
	{
		tmp = gen->mem;
		while (tmp != obj)
		{
			tmp = tmp + *(int*)(tmp);
			res++;
		}
	}	
	return (res);
}
