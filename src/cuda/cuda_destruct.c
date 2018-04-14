#include "t_cuda.h"
#include <cuda.h>
#include <cuda_runtime.h>

void		*cuda_destruct(t_cuda **ptr_cuda)
{
	t_cuda *cuda;

	if (!ptr_cuda || !(*ptr_cuda))
		return (NULL);
	cuda = *ptr_cuda;
	while (cuda->nb_mem)
	{
		if (cuda->mem[cuda->nb_mem - 1])
		{
			if ((cuda->err = cudaFree(cuda->mem[cuda->nb_mem - 1])) != cudaSuccess)
				return (cuda_ptr_error(cuda->err));
		}
		cuda->nb_mem--;
	}
	return (NULL);
}
