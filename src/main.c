/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmessina <fmessina@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/30 21:09:13 by fmessina          #+#    #+#             */
/*   Updated: 2018/04/01 18:13:23 by fmessina         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			print_usage(void)
{
	ft_putendl("\n\x1b[1;31musage: rt <scene.xml>\x1b[0m");
	exit(EXIT_FAILURE);
}

int				main(int ac, char **av)
{
	t_env		*e;

	if (ac != 2)
		print_usage();
	if (!(e = malloc(sizeof(t_env))))
		s_error("\x1b[1;31mCan't initialize RT\x1b[0m", NULL);
	ft_bzero(e, sizeof(t_env));
	if (!(e->ui = malloc(sizeof(t_ui))))
		s_error("\x1b[1;31mCan't initialize UI data structure\x1b[0m", e);
	ft_bzero(e->ui, sizeof(t_ui));
	ft_bzero(&e->ui->keys, sizeof(t_keystate));
	e->scene_file = ft_strdup(av[1]);
	e->ui->app = gtk_application_new("ray.tracer", G_APPLICATION_FLAGS_NONE);
	g_signal_connect(e->ui->app, "startup", G_CALLBACK(init), (gpointer)e);
	g_signal_connect(e->ui->app, "activate", G_CALLBACK(init_gtk), (gpointer)e);
	e->ui->gtkstatus = g_application_run(G_APPLICATION(e->ui->app), --ac, ++av);
	return (0);
}
