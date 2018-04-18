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
	cudaError_t error;

	// gtk file loading
	e->textures[slot].pixbuf = gdk_pixbuf_new_from_file(file, &e->ui->error);
	g_assert_no_error(e->ui->error);
	e->textures[slot].w = gdk_pixbuf_get_width(e->textures[slot].pixbuf);
	e->textures[slot].h = gdk_pixbuf_get_height(e->textures[slot].pixbuf);
	e->textures[slot].n_channels = gdk_pixbuf_get_n_channels(e->textures[slot].pixbuf);
	if (e->textures[slot].n_channels != 3)
		s_error("Error: incorrect texture color format", e);
	e->textures[slot].rowstride = gdk_pixbuf_get_rowstride(e->textures[slot].pixbuf);
	e->textures[slot].pixels = gdk_pixbuf_get_pixels(e->textures[slot].pixbuf);
	

	guchar	*picsou;
	int		i, j = 0;
	if (!(e->textures[slot].i_pixels = ft_memalloc(sizeof(unsigned int) * e->textures[slot].w * e->textures[slot].h)))
		s_error("Error: Failed allocate image int datas", e);
	while (j < e->textures[slot].h)
	{
		i = 0;
		while (i < e->textures[slot].w)
		{
			picsou = e->textures[slot].pixels + j * e->textures[slot].rowstride + i * e->textures[slot].n_channels;
			e->textures[slot].i_pixels[i + (j * e->textures[slot].w)] = (picsou[0] << 16) + (picsou[1] << 8) + picsou[2];
			i++;
		}
		j++;
	}
	// printf("test int %d\n", e->textures[slot].i_pixels[350 + (1024*235)]);



	// gdk pixbuf pixels copy float format
	
	// if (!(e->textures[slot].f_pixels = ft_memalloc(sizeof(float) * e->textures[slot].w * e->textures[slot].h * 4)))
	// 	s_error("Error: Failed allocate image float datas", e);
	// int		i, j;
	// i = 0;
	// j = 0;
	// while (i < (e->textures[slot].h * e->textures[slot].w * 4))
	// {
	// 	e->textures[slot].f_pixels[i++] = (float)e->textures[slot].pixels[j++] / 255.f;
	// 	e->textures[slot].f_pixels[i++] = (float)e->textures[slot].pixels[j++] / 255.f;
	// 	e->textures[slot].f_pixels[i++] = (float)e->textures[slot].pixels[j++] / 255.f;
	// 	e->textures[slot].f_pixels[i++] = 0;
	// }

	// if (slot == 0)
	// {
	// 	int x, y;
	// 	x = 350;
	// 	y = 235;
	// 	printf("\ntest x=%d y=%d | u = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y)]);
	// 	printf("test x=%d y=%d | v = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 1]);
	// 	printf("test x=%d y=%d | w = %f\n\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 2]);
	// 	x = 450;
	// 	y = 75;
	// 	printf("test x=%d y=%d | u = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y)]);
	// 	printf("test x=%d y=%d | v = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 1]);
	// 	printf("test x=%d y=%d | w = %f\n\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 2]);
	// 	x = 415;
	// 	y = 315;
	// 	printf("test x=%d y=%d | u = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y)]);
	// 	printf("test x=%d y=%d | v = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 1]);
	// 	printf("test x=%d y=%d | w = %f\n\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 2]);
	// 	x = 325;
	// 	y = 0;
	// 	printf("test x=%d y=%d | u = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y)]);
	// 	printf("test x=%d y=%d | v = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 1]);
	// 	printf("test x=%d y=%d | w = %f\n\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 2]);
	// 	x = 325;
	// 	y = 50;
	// 	printf("test x=%d y=%d | u = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y)]);
	// 	printf("test x=%d y=%d | v = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 1]);
	// 	printf("test x=%d y=%d | w = %f\n\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 2]);
	// 	x = 752;
	// 	y = 0;
	// 	printf("test x=%d y=%d | u = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y)]);
	// 	printf("test x=%d y=%d | v = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 1]);
	// 	printf("test x=%d y=%d | w = %f\n\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 2]);
	// 	x = 0;
	// 	y = 0;
	// 	printf("test x=%d y=%d | u = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y)]);
	// 	printf("test x=%d y=%d | v = %f\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 1]);
	// 	printf("test x=%d y=%d | w = %f\n\n", x, y, e->textures[slot].f_pixels[(x * 4) + (e->textures[slot].w * 4 * y) + 2]);
	// }



	// // gdk pixbuf pixels copy float3 format
	// int		i, j = 0;
	// if (!(e->textures[slot].f3_pixels = ft_memalloc(sizeof(float3) * e->textures[slot].w * e->textures[slot].h)))
	// 	s_error("Error: Failed allocate image float3 datas", e);
	// while (i < e->textures[slot].h * e->textures[slot].w)
	// {
	// 	e->textures[slot].f3_pixels[i].x = (float)e->textures[slot].pixels[j++] / 255.f;
	// 	e->textures[slot].f3_pixels[i].y = (float)e->textures[slot].pixels[j++] / 255.f;
	// 	e->textures[slot].f3_pixels[i].z = (float)e->textures[slot].pixels[j++] / 255.f;
	// 	i++;
	// }
	// printf("test fx %f\n", e->textures[slot].f3_pixels[(325)].x);
	// printf("test fy %f\n", e->textures[slot].f3_pixels[(325)].y);
	// printf("test fz %f\n\n", e->textures[slot].f3_pixels[(325)].z);


	// channelDesc
	e->textures[slot].channel_desc = cudaCreateChannelDesc(8, 8, 8, 8, \
													cudaChannelFormatKindUnsigned);



	// cudaArray
	error = cudaMallocArray(&e->textures[slot].cu_array,\
					&e->textures[slot].channel_desc,\
					e->textures[slot].w,\
					e->textures[slot].h,\
					0);
	if (error != cudaSuccess)
		fprintf(stderr, "cudaMallocArray  ERROR: %s \n", cudaGetErrorString(error));



	// cudaArray fill
	error = cudaMemcpyToArray(e->textures[slot].cu_array, 0, 0,\
					e->textures[slot].i_pixels,\
					(e->textures[slot].w) * e->textures[slot].h * sizeof(unsigned int),\
					cudaMemcpyHostToDevice);
	if (error != cudaSuccess)
		fprintf(stderr, "cudaMemcpyToArray ERROR: %s \n", cudaGetErrorString(error));



	// resDesc
	ft_memset(&e->textures[slot].res_desc, 0, \
			sizeof(e->textures[slot].res_desc));
	e->textures[slot].res_desc.resType = cudaResourceTypeArray;
	e->textures[slot].res_desc.res.array.array = e->textures[slot].cu_array;



	// texDesc
	ft_memset(&e->textures[slot].tex_desc, 0, \
				sizeof(e->textures[slot].tex_desc));
	e->textures[slot].tex_desc.addressMode[0] = cudaAddressModeWrap;
	e->textures[slot].tex_desc.addressMode[1] = cudaAddressModeWrap;
	e->textures[slot].tex_desc.filterMode = cudaFilterModePoint;
	e->textures[slot].tex_desc.readMode = cudaReadModeElementType;
	e->textures[slot].tex_desc.normalizedCoords = 1;
	e->textures[slot].tex = 0;


	// textureObject creation
	error = cudaCreateTextureObject(&e->textures[slot].tex,\
							&e->textures[slot].res_desc,\
							&e->textures[slot].tex_desc,\
							NULL);
	printf("texture \"%s\" set in slot #%d\n", file, slot);
	if (error != cudaSuccess)
		fprintf(stderr, \
		"TEXTURE cudaCreateTextureObject LOAD CUDA  ERROR: %s \n",\
		cudaGetErrorString(error));}

void	texture_load_default(t_env *e)
{
	texture_load_from_file(e, "./textures/default/0.bmp", 0);
	e->tex_0 = &e->textures[0].tex;
	texture_load_from_file(e, "./textures/default/0.bmp", 1);
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
