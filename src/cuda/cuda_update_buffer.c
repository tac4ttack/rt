#include "t_cuda.h"
#include <cuda.h>

bool		cuda_update_buffer(t_cuda *cuda, size_t size, size_t target)
{
	cudaFree(cuda->mem[target]);
	cudaMalloc(cuda->mem[target], size);
	return (true);
}
