#include "t_cuda.h"
#include <cuda.h>
#include <cuda_runtime.h>

void	*cuda_ptr_error(cudaError_t code)
{
	ft_putstr_fd("Cuda error :\n", 2);
	ft_putstr_fd(cudaGetErrorString(code), 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

bool	cuda_error(cudaError_t code)
{
	ft_putstr_fd("Cuda error :\n", 2);
	ft_putstr_fd(cudaGetErrorString(code), 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}
