/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:31:06 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/21 18:05:23 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cuda_print_mem(void)
{
	int						device_id;
	size_t 					mem_free;
	size_t 					mem_total;
	struct cudaDeviceProp	device_prop;
	char					*str;

	device_id = 0;
	cudaSetDevice(device_id);
	cudaGetDeviceProperties(&device_prop, device_id);
	cudaMemGetInfo(&mem_free, &mem_total);
	ft_putstr("\nDevice ");
	ft_putnbr(device_id);
	ft_putstr(" ");
	ft_putstr(device_prop.name);
	ft_putstr(" ");
	str = ft_ftoa((float)mem_free / (1024 * 1024));
	ft_putstr(str);
	free(str);
	ft_putstr(" MB Free of ");
	str = ft_ftoa((float)mem_total / (1024 * 1024));
	ft_putstr(str);
	free(str);
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

void waiting(char *str) {
	static int a = 999;
	int b;
	printf("// waiting att %i %s\n", a, str);
	scanf("%i", &b);
	a++;
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
	// waiting("1");
	ft_memdel((void**)&e->textures);
	// waiting("2");
	if (e->cuda)
		cuda_destruct(&e->cuda);
	// waiting("2.5");
	gen_destruct(&e->gen_objects);
	// waiting("3");
	gen_destruct(&e->gen_lights);
	// waiting("4");
	if (e->ui->surface)
		cairo_surface_destroy(e->ui->surface);
	// waiting("4.5");
	g_object_unref(e->ui->pixbuf);
	// waiting("5");
	if (e->xml->nodes)
		xml_node_clean(&e->xml->nodes);
	// waiting("7");
	if (e->xml->sub_node)
		xml_node_clean(&e->xml->sub_node);
	// waiting("8");
	ft_memdel((void**)&e->xml);
	ft_putendl("\x1b[1;29mFreed XML ressources\x1b[0m");
	// waiting("9");
	ft_memdel((void**)&e->cameras);
	ft_putendl("\x1b[1;29mFreed cameras array\x1b[0m");
	// waiting("10");
	ft_memdel((void**)&e->scene);
	ft_putendl("\x1b[1;29mFreed scene datas\x1b[0m");
	// waiting("11");
	ft_memdel((void**)&e->pixel_data);
	ft_putendl("\x1b[1;29mFreed pixel buffer\x1b[0m");
	// waiting("12");
	ft_memdel((void**)&e->ui);
	ft_putendl("\x1b[1;29mFreed UI environnement\x1b[0m");
	// waiting("13");
	ft_memdel((void**)&e);
	ft_putendl("\x1b[1;29mFreed RT environnement\x1b[0m");
	// waiting("14");
}

void	s_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[1;31mOh no I just crashed!\x1b[0m");
	ft_putendl(str);
	if (e)
		flush(e);
	cuda_print_mem();
	cudaDeviceReset();
	exit(EXIT_FAILURE);
}

void	p_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[1;31mOh no I just crashed!\x1b[0m");
	perror((const char *)str);
	flush(e);
	cuda_print_mem();
	cudaDeviceReset();
	exit(EXIT_FAILURE);
}

int		quit(t_env *e)
{
	flush(e);
	cuda_print_mem();
	cudaDeviceReset();
	ft_putendl("Exiting");
	exit(EXIT_SUCCESS);
	return (0);
}

int		gtk_quit(GtkApplication *app, gpointer data)
{
	t_env *e;
	int		lol;

	(void)app;
	e = data;
	// waiting("++1\n");
	gtk_main_quit();
	// waiting("++2\n");
	gtk_widget_destroy(e->ui->main_window);
	// waiting("++3\n");
	g_object_unref(e->ui->app);
	// waiting("++4\n");
	ft_putendl("\n\x1b[1;32mExiting...\x1b[0m");
	// waiting("++5\n");
	flush(e);
	// waiting("++6\n");
	cuda_print_mem();
	// waiting("++7\n");
	cudaDeviceReset();
	// waiting("++8\n");
	ft_putendl("\x1b[1;41mSee you space clodo!\x1b[0m");

	int i = 0;
	while (i < 99999999999)
		i++;

	exit(EXIT_SUCCESS);
	return (0);
}
