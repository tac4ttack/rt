#include "rt.h"

static void		texture_load_from_file(t_env *e, char *file, int slot)
{
	cudaError_t error;

	e->textures[slot].pixbuf = gdk_pixbuf_new_from_file(file, &e->ui->error);
	g_assert_no_error(e->ui->error);
	e->textures[slot].w = gdk_pixbuf_get_width(e->textures[slot].pixbuf);
	e->textures[slot].h = gdk_pixbuf_get_height(e->textures[slot].pixbuf);
	e->textures[slot].n_cha = gdk_pixbuf_get_n_channels( \
													e->textures[slot].pixbuf);
	if (e->textures[slot].n_cha != 3)
		s_error("Error: incorrect texture color format", e);
	e->textures[slot].rows = gdk_pixbuf_get_rowstride(e->textures[slot].pixbuf);
	e->textures[slot].pixels = gdk_pixbuf_get_pixels(e->textures[slot].pixbuf);
	e->scene->tex_res[slot].x = e->textures[slot].w;
	e->scene->tex_res[slot].y = e->textures[slot].h;
}	

static void 	texture_copy_raw_data(t_env *e, t_texture *texture)
{
	guchar		*pixel;
	int			i;
	int			j;

	i = 0;
	j = 0;
	if (!(texture->i_pixels = ft_memalloc(sizeof(unsigned int) * texture->w * texture->h)))
		s_error("Error: Failed allocate image int datas", e);
	while (j < texture->h)
	{
		i = 0;
		while (i < texture->w)
		{
			pixel = texture->pixels + j * texture->rows + i * texture->n_cha;
			texture->i_pixels[i + (j * texture->w)] = (pixel[0] << 16) + (pixel[1] << 8) + pixel[2];
			i++;
		}
		j++;
	}
}

static void		texture_create_cudarray(t_env *e, t_texture *texture)
{
	cudaError_t error;

	texture->channel_desc = cudaCreateChannelDesc(32, 0, 0, 0, \
											cudaChannelFormatKindUnsigned);
	error = cudaMallocArray(&texture->cu_array, &texture->channel_desc, \
							texture->w, texture->h, 0);
	if (error != cudaSuccess)
	{
		ft_putendl(cudaGetErrorString(error));
		s_error("\x1b[2;31mError can't create texture array\x1b[0m", e);
	}
	error = cudaMemcpyToArray(texture->cu_array, 0, 0,\
					texture->i_pixels,\
					(texture->w) * texture->h * sizeof(unsigned int),\
					cudaMemcpyHostToDevice);
	if (error != cudaSuccess)
	{
		ft_putendl(cudaGetErrorString(error));
		s_error("\x1b[2;31mError can't copy texture to array\x1b[0m", e);
	}
	ft_memset(&texture->res_desc, 0, \
			sizeof(texture->res_desc));
	texture->res_desc.resType = cudaResourceTypeArray;
	texture->res_desc.res.array.array = texture->cu_array;
}

static void		texture_finalize_object(t_env *e, t_texture *texture)
{
	cudaError_t error;

	ft_memset(&texture->tex_desc, 0, \
				sizeof(texture->tex_desc));
	texture->tex_desc.addressMode[0] = cudaAddressModeWrap;
	texture->tex_desc.addressMode[1] = cudaAddressModeWrap;
	texture->tex_desc.filterMode = cudaFilterModePoint;
	texture->tex_desc.readMode = cudaReadModeElementType;
	texture->tex_desc.normalizedCoords = FALSE;
	texture->tex = 0;
	error = cudaCreateTextureObject(&texture->tex,\
							&texture->res_desc,\
							&texture->tex_desc,\
							NULL);
	if (error != cudaSuccess)
	{
		ft_putendl(cudaGetErrorString(error));
		s_error("\x1b[2;31mError can't create texture object\x1b[0m", e);
	}
}

void	texture_init(t_env *e)
{
	if (!(e->textures = ft_memalloc(sizeof(t_texture) * 5)))
		s_error("Error: Failed allocate host textures data", e);
	texture_load_from_file(e, "./textures/default/0.bmp", 0);
	texture_copy_raw_data(e, &e->textures[0]);
	texture_create_cudarray(e, &e->textures[0]);
	texture_finalize_object(e, &e->textures[0]);
	e->scene->tex[0] = e->textures[0].tex;
	texture_load_from_file(e, "./textures/default/1.bmp", 1);
	texture_copy_raw_data(e, &e->textures[1]);
	texture_create_cudarray(e, &e->textures[1]);
	texture_finalize_object(e, &e->textures[1]);
	e->scene->tex[1] = e->textures[1].tex;
	texture_load_from_file(e, "./textures/default/6.bmp", 2);
	texture_copy_raw_data(e, &e->textures[2]);
	texture_create_cudarray(e, &e->textures[2]);
	texture_finalize_object(e, &e->textures[2]);
	e->scene->tex[2] = e->textures[2].tex;
	texture_load_from_file(e, "./textures/default/4.bmp", 3);
	texture_copy_raw_data(e, &e->textures[3]);
	texture_create_cudarray(e, &e->textures[3]);
	texture_finalize_object(e, &e->textures[3]);
	e->scene->tex[3] = e->textures[3].tex;
	texture_load_from_file(e, "./textures/default/skybox.bmp", 4);
	texture_copy_raw_data(e, &e->textures[4]);
	texture_create_cudarray(e, &e->textures[4]);
	texture_finalize_object(e, &e->textures[4]);
	e->scene->tex[4] = e->textures[4].tex;
}
