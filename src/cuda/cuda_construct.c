#include "t_cuda.h"
# include <cuda.h>

t_cuda		*cuda_construct()
{
	t_cuda *cuda;

	if (!(cuda = ft_memalloc(sizeof(t_cuda))))
		return (NULL);
	cuda->add_buffer = cuda_add_buffer;
	cuda->update_buffer = cuda_update_buffer;
	return (cuda);
}
