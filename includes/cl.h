#ifndef CL_H
# define CL_H

# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif

# include "libft.h"

# define MAX_SOURCE_SIZE			(0x100000)
# define CL_ERROR_LEN_BUFFER		17000

typedef struct			s_cl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	size_t				nb_mem;
	cl_mem				*mem;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_int				err;
	size_t				global_item_size;
	size_t				local_item_size;
	size_t				dimension[2];
	char				*kernel_src;
	size_t				src_size;
	cl_event			event;
	bool				(*add_buffer)(struct s_cl *, size_t);
	bool				(*compute)(struct s_cl *);
}						t_cl;

t_cl					*cl_construct(const char *path, const char *name, \
							const size_t width, const size_t height, int type);
void					*cl_destruct(t_cl **ptr_cl);
bool					cl_add_buffer(t_cl *cl, size_t size);
bool					cl_print_error(int err);
bool					cl_compute(t_cl *cl);

#endif
