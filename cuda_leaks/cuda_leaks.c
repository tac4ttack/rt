#include <cuda_runtime.h>
#include <cuda.h>
#include <stdlib.h>

int	main(void)
{
	void	*cuda_mem;

	cuda_mem = NULL;
	cudaMalloc(&cuda_mem, 4096);
	cudaFree(cuda_mem);
	cuda_mem = NULL;
	cudaDeviceReset();
	while (1)
		;
	return (0);
}
