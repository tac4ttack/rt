#ifndef T_CUDA_H
# define T_CUDA_H

#include "libft.h"
#include <stdbool.h>
#include <cuda_runtime.h>

typedef struct			s_cuda
{
	size_t				nb_mem;
	void				**mem;
	cudaError_t			err;
	bool				(*add_buffer)(struct s_cuda *, size_t);
	bool				(*update_buffer)(struct s_cuda *, size_t, size_t);
}						t_cuda;

t_cuda					*cuda_construct();
void					*cuda_destruct();
bool					cuda_add_buffer(t_cuda *cuda, size_t size);
bool					cuda_update_buffer(t_cuda *cuda, size_t size, size_t target);
bool					cuda_error(cudaError_t code);
void					*cuda_ptr_error(cudaError_t code);

#endif
