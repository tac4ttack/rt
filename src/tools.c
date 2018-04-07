/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:31:06 by adalenco          #+#    #+#             */
/*   Updated: 2018/04/07 15:20:24 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	flush(t_env *e)
{
	int i;

	i = 0;
	if (e)
	{
		while (i < NB_TEXTURE)
		{
			ft_memdel((void **)&e->texture[i].pixel_array);
			i++;
		}
		ft_memdel((void **)&e->texture);
		if (e->cl)
		{
			cl_destruct(&e->cl);
			gen_destruct(&e->gen_objects);
			gen_destruct(&e->gen_lights);
		}
		if (e->ui->surface)
			cairo_surface_destroy(e->ui->surface);
		if (XML)
			free(XML);
		ft_putendl("\x1b[1;29mFreed XML ressources\x1b[0m");
		if (e)
			free(e);
		ft_putendl("\x1b[1;29mFreed RT environnement\x1b[0m");
	}
}

void	s_error(char *str, t_env *e)
{
	ft_putendl("\n\x1b[1;31mOh no I just crashed!\x1b[0m");
	ft_putendl(str);
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
	g_object_unref(e->ui->app);
	ft_putendl("\n\x1b[1;32mExiting...\x1b[0m");
	flush(e);
	ft_putendl("\x1b[1;41mSee you space clodo!\x1b[0m");
	ft_bzero(e, sizeof(t_env ));
	// DEBUG
	// while (1)
	// 	;
	exit(EXIT_SUCCESS);
	return (0);
}
