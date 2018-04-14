/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:31:06 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/14 22:18:33 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	flush(t_env *e)
{
	int i;

	i = -1;
	while (++i < NB_TEXTURE)
		if (e->texture[i].pixel_array)
			ft_memdel((void **)&e->texture[i].pixel_array);
	ft_memdel((void **)&e->texture);
	if (e->cuda)
		cuda_destruct(&e->cuda);
	gen_destruct(&e->gen_objects);
	gen_destruct(&e->gen_lights);
	if (e->ui->surface)
		cairo_surface_destroy(e->ui->surface);
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
	exit(EXIT_FAILURE);
}

void	p_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[1;31mOh no I just crashed!\x1b[0m");
	perror((const char *)str);
	flush(e);
	exit(EXIT_FAILURE);
}

int		quit(t_env *e)
{
	flush(e);
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
	//test
	cudaDeviceReset();
	ft_putendl("\x1b[1;41mSee you space clodo!\x1b[0m");
	exit(EXIT_SUCCESS);
	return (0);
}
