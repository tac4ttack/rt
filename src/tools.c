/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adalenco <adalenco@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:31:06 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/21 20:43:46 by ntoniolo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			waiting(char *str)
{
	static int	a = 999;
	int			b;

	printf("// waiting att %i %s\n", a, str);
	scanf("%i", &b);
	a++;
}

void			texture_destroy(t_env *e, t_texture *tex)
{
	if (tex && e->cuda)
	{
		if ((e->cuda->err = cudaDestroyTextureObject(tex->tex)) != cudaSuccess)
			cuda_error(e->cuda->err);
		if ((e->cuda->err = cudaFreeArray(tex->cu_array)) != cudaSuccess)
			cuda_error(e->cuda->err);
	}
	if (tex)
	{
		g_object_unref(tex->pixbuf);
		ft_memdel((void**)&tex->i_pixels);
	}
}

int				quit(t_env *e)
{
	if (e)
		flush(e);
	cudaDeviceReset();
	ft_putendl("Exiting");
	exit(EXIT_SUCCESS);
	return (0);
}

int				gtk_quit(GtkApplication *app, gpointer data)
{
	t_env	*e;

	(void)app;
	e = data;
	gtk_main_quit();
	if (e->ui)
	{
		gtk_widget_destroy(e->ui->main_window);
		g_object_unref(e->ui->app);
	}
	ft_putendl("\n\x1b[1;32mExiting...\x1b[0m");
	if (e)
		flush(e);
	cudaDeviceReset();
	waiting("This is the end...\n");
	ft_putendl("\x1b[1;41mSee you space clodo!\x1b[0m");
	exit(EXIT_SUCCESS);
	return (0);
}
