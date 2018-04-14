#include "rt.h"
#include "t_cuda.h"
#include <cuda.h>
#include <cuda_runtime.h>

void	init_kernel(t_env *e)
{
	t_scene		*scene;
	t_gen		*gen_objects;
	t_gen		*gen_lights;
	t_tex		*texture;
	t_cuda		*cuda;

	scene = e->scene;
	gen_objects = e->gen_objects;
	gen_lights = e->gen_lights;
	texture = e->texture;
	e->cuda = cuda_construct();
	cuda = e->cuda;
	//if (!(e->cuda = cuda_construct()))
		//return ();

		printf("2\n");
	cuda_add_buffer(cuda, scene->win_w * scene->win_h * sizeof(int));
	cuda_add_buffer(cuda, gen_objects->mem_size);
	cuda_add_buffer(cuda, gen_lights->mem_size);
	cuda_add_buffer(cuda, sizeof(t_scene));
	cuda_add_buffer(cuda, sizeof(t_cam) * scene->n_cams);
	cuda_add_buffer(cuda, sizeof(unsigned int));
	cuda_add_buffer(cuda, sizeof(unsigned int) * texture[0].width * texture[0].height);
	cuda_add_buffer(cuda, sizeof(unsigned int) * texture[1].width * texture[1].height);
//	cuda_add_buffer(cuda, sizeof(unsigned int) * texture[2].width * texture[2].height);

	cudaMemcpy(cuda->mem[6], texture[0].pixel_array, sizeof(unsigned int) * texture[0].width * texture[0].height, cudaMemcpyHostToDevice);
	cudaMemcpy(cuda->mem[7], texture[1].pixel_array, sizeof(unsigned int) * texture[1].width * texture[1].height, cudaMemcpyHostToDevice);
	//cudaMemcpy(cuda->mem[8], texture[2].pixel_array, sizeof(unsigned int) * texture[2].width * texture[2].height, cudaMemcpyHostToDevice);
	//cudaMemcpy(cuda->texture_3, texture[3].pixel_array, sizeof(unsigned int) * texture[3].width * texture[3].height, cudaMemcpyHostToDevice);
}
