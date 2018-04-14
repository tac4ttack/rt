#include "t_cuda.h"
#include <cuda.h>
#include <cuda_runtime.h>

bool		cuda_update_buffer(t_cuda *cuda, size_t size, size_t target)
{
	printf("cc\n");
	if ((cuda->err = cudaFree(cuda->mem[target]))!= cudaSuccess)
		return (cuda_error(cuda->err));
	if ((cuda->err = cudaMalloc(&(cuda->mem[target]), size) != cudaSuccess))
		return (cuda_error(cuda->err));
	return (true);
}
