#include "rt.h"

void	texture_destroy(t_env *e, t_texture *tex)
{
	cudaDestroyTextureObject(tex->tex);
	cudaFreeArray(tex->cu_array);
	g_object_unref(tex->pixbuf);
	ft_memdel((void**)&tex);
}

void	texture_load_from_file(t_env *e, char *file, int slot)
{
	e->textures[slot].pixbuf = gdk_pixbuf_new_from_file(file, &e->ui->error);
	g_assert_no_error(e->ui->error);
	e->textures[slot].w = gdk_pixbuf_get_width(e->textures[slot].pixbuf);
	e->textures[slot].h = gdk_pixbuf_get_height(e->textures[slot].pixbuf);
	e->textures[slot].pixels = gdk_pixbuf_get_pixels(e->textures[slot].pixbuf);
	e->textures[slot].channel_desc = cudaCreateChannelDesc(32, 0, 0, 0, \
													cudaChannelFormatKindFloat);
	cudaMallocArray(&e->textures[slot].cu_array,\
					&e->textures[slot].channel_desc,\
					e->textures[slot].w,\
					e->textures[slot].h,\
					0);
	cudaMemcpyToArray(e->textures[slot].cu_array, 0, 0,\
					e->textures[slot].pixels,\
					e->textures[slot].w * e->textures[slot].h * sizeof(char),\
					cudaMemcpyHostToDevice);
	ft_memset(&e->textures[slot].tex_desc, 0, sizeof(e->textures[slot].tex_desc));
	e->textures[slot].tex_desc.addressMode[0] = cudaAddressModeWrap;
	e->textures[slot].tex_desc.addressMode[1] = cudaAddressModeWrap;
	e->textures[slot].tex_desc.filterMode = cudaFilterModeLinear;
	e->textures[slot].tex_desc.readMode = cudaReadModeElementType;
	e->textures[slot].tex_desc.normalizedCoords = 1;
	e->textures[slot].tex = 0;
	cudaCreateTextureObject(&e->textures[slot].tex,\
							&e->textures[slot].res_desc,\
							&e->textures[slot].tex_desc,\
							NULL);
	
}

void	texture_load_default(t_env *e)
{
	texture_load_from_file(e, "./textures/default/0.bmp", 0);
	e->tex_0 = &e->textures[0].tex;
	texture_load_from_file(e, "./textures/default/1.bmp", 1);
	e->tex_1 = &e->textures[1].tex;
	texture_load_from_file(e, "./textures/default/0.bmp", 2);
	e->tex_2 = &e->textures[2].tex;
	texture_load_from_file(e, "./textures/default/0.bmp", 3);
	e->tex_3 = &e->textures[3].tex;
}

void	texture_init(t_env *e)
{
	if (!(e->textures = ft_memalloc(sizeof(t_texture) * 4)))
		s_error("Error: Failed allocate host textures data", e);
	texture_load_default(e);
}
