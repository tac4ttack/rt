/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:31:06 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/20 15:56:25 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			cuda_print_mem(void)
{
	int						device_id;
	size_t 					mem_free;
	size_t 					mem_total;
	struct cudaDeviceProp	device_prop;

	cudaSetDevice(device_id);
	cudaGetDeviceProperties(&device_prop, device_id);
	cudaMemGetInfo(&mem_free, &mem_total);
	ft_putstr("\nDevice ");
	ft_putnbr(device_id);
	ft_putstr(" ");
	ft_putstr(device_prop.name);
	ft_putstr(" ");
	ft_putstr(ft_ftoa((float)mem_free / (1024 * 1024)));
	ft_putstr(" MB Free of ");
	ft_putstr(ft_ftoa((float)mem_total / (1024 * 1024)));
	ft_putstr(" MB Total\n");
}

void			texture_destroy(t_env *e, t_texture *tex)
{

	if ((e->cuda->err = cudaDestroyTextureObject(tex->tex)) != cudaSuccess)
		cuda_error(e->cuda->err);
	if ((e->cuda->err = cudaFreeArray(tex->cu_array)) != cudaSuccess)
		cuda_error(e->cuda->err);
	g_object_unref(tex->pixbuf);
	ft_memdel((void**)&tex->i_pixels);
}


void	flush(t_env *e)
{
	int i;

	i = 0;
	if (e->textures)
		while (i < 5)
		{
			texture_destroy(e, &e->textures[i]);
			i++;
		}
	ft_memdel((void**)&e->textures);
	if (e->cuda)
		cuda_destruct(&e->cuda);
	gen_destruct(&e->gen_objects);
	gen_destruct(&e->gen_lights);
	if (e->ui->surface)
		cairo_surface_destroy(e->ui->surface);
	g_object_unref(e->ui->pixbuf);
	ft_memdel((void**)&e->xml);
	ft_putendl("\x1b[1;29mFreed XML ressources\x1b[0m");
	ft_memdel((void**)&e->cameras);
	ft_putendl("\x1b[1;29mFreed cameras array\x1b[0m");
	ft_memdel((void**)&e->scene);
	ft_putendl("\x1b[1;29mFreed scene datas\x1b[0m");
	ft_memdel((void**)&e->pixel_data);
	ft_putendl("\x1b[1;29mFreed pixel buffer\x1b[0m");
	ft_memdel((void**)&e->ui);
	ft_putendl("\x1b[1;29mFreed UI environnement\x1b[0m");
	ft_memdel((void**)&e);
	ft_putendl("\x1b[1;29mFreed RT environnement\x1b[0m");
}

void	s_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[1;31mOh no I just crashed!\x1b[0m");
	ft_putendl(str);
	if (e)
		flush(e);
	cuda_print_mem();
	exit(EXIT_FAILURE);
}

void	p_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[1;31mOh no I just crashed!\x1b[0m");
	perror((const char *)str);
	flush(e);
	cuda_print_mem();
	exit(EXIT_FAILURE);
}

int		quit(t_env *e)
{
	flush(e);
	cuda_print_mem();
	ft_putendl("Exiting");
	exit(EXIT_SUCCESS);
	return (0);
}

int		gtk_quit(GtkApplication *app, gpointer data)
{
	t_env *e;
	
	(void)app;
	e = data;
	gtk_main_quit();
	gtk_widget_destroy(e->ui->main_window);
	g_object_unref(e->ui->app);
	ft_putendl("\n\x1b[1;32mExiting...\x1b[0m");
	flush(e);
	cuda_print_mem();
	cudaDeviceReset();
	ft_putendl("\x1b[1;41mSee you space clodo!\x1b[0m");
	exit(EXIT_SUCCESS);
	return (0);
}
