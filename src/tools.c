/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 19:31:06 by adalenco          #+#    #+#             */
/*   Updated: 2018/03/07 19:36:37 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	flush(t_env *e)
{
	if (e)
	{
		destruct_cl(&e->cl);
		destruct_gen(&e->gen_objects);
		destruct_gen(&e->gen_lights);
		if (e->kernel_src)
			free(e->kernel_src);
		ft_putendl("\x1b[1;29mFreed Kernel sources\x1b[0m");
		if (XML)
			free(XML);
		ft_putendl("\x1b[1;29mFreed XML ressources\x1b[0m");
		
// WILL BE REMOVED AFTER GETTING RID OF MLX!
//	if (e->frame && e->frame->ptr)
//		mlx_destroy_image(e->mlx, e->frame->ptr);
//		ft_putendl("3");
//	if (e->frame)
//		free(e->frame);
//		ft_putendl("4");
//	if (e->win)
//		mlx_destroy_window(e->mlx, e->win);

		// GTK SHIT
		if (e->ui->icon)
			g_object_unref(e->ui->icon);
		ft_putendl("\x1b[1;29mFreed the GTK Icon\x1b[0m");
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
	
	e = data;
	ft_putendl("\n\x1b[1;32mExiting...\x1b[0m");
	flush(e);
	g_object_unref(app);
	ft_putendl("\x1b[1;29mFreed the GTK App\x1b[0m");
	ft_putendl("\x1b[1;41mSee you space clodo!\x1b[0m");
//	gtk_main_quit();
	exit(EXIT_SUCCESS);
	return (0);
}
