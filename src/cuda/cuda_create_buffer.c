#include "t_cuda.h"
#include <cuda.h>
#include <cuda_runtime.h>

bool		cuda_add_buffer(t_cuda *cuda, size_t size)
{
	printf("3\n");
	if (!(cuda->mem = ft_memrealloc(cuda->mem,
					sizeof(void **) * cuda->nb_mem,
					sizeof(void **) * (cuda->nb_mem + 1))))
		return (false);
	printf("5\n");
	cudaMalloc(&(cuda->mem[cuda->nb_mem]), size);;
	cuda->nb_mem++;
	return (true);
}
